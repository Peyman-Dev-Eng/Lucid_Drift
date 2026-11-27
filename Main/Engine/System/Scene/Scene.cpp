/*
 * Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */

#include "Scene.h"
#include <typeinfo>
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "Actors/Line/Line.h"
#include "System/Core/Core.h"

LDDrift::Scene::Scene() = default;

LDDrift::Scene::~Scene() {
    for (auto& [circleName, circle,Render] : circleShapes) {
        delete circle;
    }
    for (auto& [polygonName, polygon,Render] : polygonShapes) {
        delete polygon;
    }
    for (auto& [lineName, line,Render] : lines) {
        delete line;
    }
    for (auto& [textureName, texture,Render] : textures) {
        texture->FreeTexture();
        delete texture;
    }
}

void LDDrift::Scene::SetCorePTR(LDDrift::Core* corePtr) {
    NPV_assert(corePtr);
    core = corePtr;
}

void LDDrift::Scene::SetRendererPTR(LDDrift::ShapeRender* rendererPTR) {
    NPV_assert(rendererPTR);
    shape_render = rendererPTR;
}

void LDDrift::Scene::ReSendShapesToRender() {
    if (sendDataToGPU == false) {
        return;
    }

    NPV_assert(shape_render)
    NPV_assert(texture_render);

    texture_render->AddTexture(&backgroundTexture, 0);

    for (const auto& [actorType, index] : managements) {
        if (actorType == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C) {
            shape_render->AddShapeToRender(circleShapes[index].circle);
        } else if (actorType == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P) {
            shape_render->AddShapeToRender(polygonShapes[index].polygon);
        } else if (actorType == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L) {
            shape_render->AddLineToRender(lines[index].line);
        } else if (actorType == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_T) {
            texture_render->AddTexture(textures[index].texture, 1);
        }
    }

    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
    texture_render->SendToGPU();
    sendDataToGPU = false;
}

LDDrift::Actors::Circle* LDDrift::Scene::GetCircle(const std::string& name) const {
    for (const auto& [circleName, circle,Render] : circleShapes) {
        if (circleName == name) {
            return circle;
        }
    }
    return nullptr;
}


void LDDrift::Scene::CreateCircleShape(const std::string& name, const int _pointCount, const int _radius,
                                       const int _speed, const LDDrift::VecPos2D& pos, const LDDrift::VecCol& color,
                                       const float thickness) {
    const CIRCLE_SHAPE_INFORMATION newCircle{
        .circleName = name, .circle = new LDDrift::Actors::Circle(), .render = true
    };
    newCircle.circle->SetType<LDDrift::ActorType::convex>();
    if (thickness != -1) {
        newCircle.circle->SetJoinLineAlgorithm(LDDrift::JoinLineType::Bevel);
        newCircle.circle->SetThickness(thickness);
    }
    newCircle.circle->SetCirclePosition(pos);
    newCircle.circle->SetPointCount(_pointCount);
    newCircle.circle->SetScreenSize(core->window.GetViewportSize());
    newCircle.circle->SetRadius(static_cast<float>(_radius));
    newCircle.circle->SetSpeed(static_cast<float>(_speed));
    newCircle.circle->SetAllPointsColor(color);
    newCircle.circle->Rebuild();
    newCircle.circle->SetOriginalPositionToCenter();
    circleShapes.push_back({.circleName = newCircle.circleName, .circle = newCircle.circle});
    managements.push_back(QueueManagement{
        .searchInVector = LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C, .index = circleShapes.size() - 1
    });
    shape_render->AddShapeToRender(newCircle.circle);
    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
}

LDDrift::Actors::Polygon* LDDrift::Scene::GetPolygon(const std::string& name) const {
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        if (polygonName == name) {
            return polygon;
        }
    }
    return nullptr;
}

void LDDrift::Scene::CreatePolygonShape(const std::string& name, const int _pointCount, const int _speed,
                                        const int* pos,
                                        const LDDrift::VecCol& color, const float thickness, const int joinLine_A) {
    const POLYGON_SHAPE_INFORMATION newPolygon{
        .polygonName = name, .polygon = new LDDrift::Actors::Polygon(), .render = true
    };
    if (thickness != -1) {
        if (joinLine_A == MITER) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Miter);
        } else if (joinLine_A == ROUND) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Round);
        } else if (joinLine_A == BEVEL) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Bevel);
        }
        newPolygon.polygon->SetThickness(thickness);
    }
    newPolygon.polygon->SetPointCount(_pointCount);
    newPolygon.polygon->SetScreenSize(core->window.GetViewportSize());
    newPolygon.polygon->SetSpeed(static_cast<float>(_speed));
    newPolygon.polygon->SetAllPointsColor(color);
    for (int pointIndex = 0; pointIndex < _pointCount; ++pointIndex) {
        newPolygon.polygon->SetPoint(pointIndex, {
                                         static_cast<float>(pos[pointIndex * 2]),
                                         static_cast<float>(pos[pointIndex * 2 + 1])
                                     });
    }
    if (newPolygon.polygon->ShapeIsConcave()) {
        newPolygon.polygon->SetType<LDDrift::ActorType::concave>();
    } else {
        newPolygon.polygon->SetType<LDDrift::ActorType::convex>();
    }
    newPolygon.polygon->SetOriginalPositionToCenter();
    polygonShapes.push_back({.polygonName = newPolygon.polygonName, .polygon = newPolygon.polygon});
    managements.push_back(QueueManagement{
        .searchInVector = LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P, .index = polygonShapes.size() - 1
    });
    shape_render->AddShapeToRender(newPolygon.polygon);
    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
}

void LDDrift::Scene::CreateLineActor(const std::string& name, const int _thickness, const int* startPos,
                                     const int* endPos,
                                     const LDDrift::VecCol& color) {
    const LINE_ACTOR_INFORMATION newLine{
        .lineName = name, .line = new LDDrift::Actors::Line(
            {static_cast<float>(startPos[0]), static_cast<float>(startPos[1])},
            {static_cast<float>(endPos[0]), static_cast<float>(endPos[1])}),
        .render = true
    };
    newLine.line->SetScreenSize(core->window.GetViewportSize());
    newLine.line->SetThickness(static_cast<float>(_thickness));
    newLine.line->SetLineColor(color);
    newLine.line->CreateTriangles();
    lines.push_back({.lineName = newLine.lineName, .line = newLine.line});
    managements.push_back(QueueManagement{
        .searchInVector = LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L, .index = lines.size() - 1
    });
    shape_render->AddLineToRender(newLine.line);
    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
}

LDDrift::Actors::Line* LDDrift::Scene::GetLine(const std::string& name) const {
    for (const auto& [lineName, line,Render] : lines) {
        if (lineName == name) {
            return line;
        }
    }
    return nullptr;
}

bool LDDrift::Scene::FindCircleWithName(const std::string& name) const {
    for (const auto& [lineName, line,Render] : circleShapes) {
        if (lineName == name) {
            return true;
        }
    }
    return false;
}

void LDDrift::Scene::freeSavedData() {
    hasData = false;
    for (const auto& [circlePTR, color] : circle_colors) {
        for (std::size_t i = 0; i < circlePTR->GetPointCount(); ++i) {
            circlePTR->SetPointColor(i, color[i]);
        }
    }
    for (const auto& [polygonPTR, color] : polygon_colors) {
        for (std::size_t i = 0; i < polygonPTR->GetPointCount(); ++i) {
            polygonPTR->SetPointColor(i, color[i]);
        }
    }
    for (const auto& [linePTR, color] : line_colors) {
        linePTR->SetLineColor(color);
    }
    for (const auto& [texturePTR, texture_MULTI] : texture_multipliers) {
        texturePTR->SetColorMultiplierForTexture(texture_MULTI);
    }
    circle_colors.clear();
    polygon_colors.clear();
    line_colors.clear();
    texture_multipliers.clear();
}

bool LDDrift::Scene::FindPolygonWithName(const std::string& name) const {
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        if (polygonName == name) {
            return true;
        }
    }
    return false;
}

bool LDDrift::Scene::FindLineWithName(const std::string& name) const {
    for (const auto& [lineName, line,Render] : lines) {
        if (lineName == name) {
            return true;
        }
    }
    return false;
}

void LDDrift::Scene::CreatePolygonShape(const std::string& name, const int _pointCount, const int _speed,
                                        const int* pos,
                                        const std::pmr::vector<LDDrift::VecCol>& colors, const float thickness,
                                        const int joinLine_A) {
    const POLYGON_SHAPE_INFORMATION newPolygon{
        .polygonName = name, .polygon = new LDDrift::Actors::Polygon(), .render = true
    };
    if (thickness != 0.0f) {
        if (joinLine_A == MITER) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Miter);
        } else if (joinLine_A == ROUND) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Round);
        } else if (joinLine_A == BEVEL) {
            newPolygon.polygon->SetJoinLineAlgorithm(LDDrift::JoinLineType::Bevel);
        }
        newPolygon.polygon->SetThickness(thickness);
    }
    newPolygon.polygon->SetPointCount(_pointCount);
    newPolygon.polygon->SetScreenSize(core->window.GetViewportSize());
    newPolygon.polygon->SetSpeed(static_cast<float>(_speed));
    int counter = 0;
    for (const LDDrift::VecCol& color : colors) {
        newPolygon.polygon->SetPointColor(counter++, color);
    }
    for (int pointIndex = 0; pointIndex < _pointCount; ++pointIndex) {
        newPolygon.polygon->SetPoint(pointIndex, {
                                         static_cast<float>(pos[pointIndex * 2]),
                                         static_cast<float>(pos[pointIndex * 2 + 1])
                                     });
    }
    if (newPolygon.polygon->ShapeIsConcave()) {
        newPolygon.polygon->SetType<LDDrift::ActorType::concave>();
    } else {
        newPolygon.polygon->SetType<LDDrift::ActorType::convex>();
    }
    newPolygon.polygon->SetOriginalPositionToCenter();
    polygonShapes.push_back({.polygonName = newPolygon.polygonName, .polygon = newPolygon.polygon});
    managements.push_back(QueueManagement{
        .searchInVector = LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P, .index = polygonShapes.size() - 1
    });
    shape_render->AddShapeToRender(newPolygon.polygon);
    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
}

void LDDrift::Scene::MarkSendDataToGPU() {
    sendDataToGPU = true;
}

bool LDDrift::Scene::DeletePolygonShape(const std::string& name) {
    long int pos = 0;
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        if (polygonName == name) {
            polygonShapes.erase(polygonShapes.begin() + pos);
            core->shape_render.RemoveShapeFromRender(polygon);
            core->shape_render.UpdateShapeData();
            DeleteWithIndexFromManagements(LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P, pos);
            for (auto& [searchInVector, index] : managements) {
                if (searchInVector == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P && index > pos) {
                    --index;
                }
            }
            return true;
        }
        ++pos;
    }
    return false;
}

bool LDDrift::Scene::DeleteLineShape(const std::string& name) {
    long int pos = 0;
    for (const auto& [lineName, line,Render] : lines) {
        if (lineName == name) {
            lines.erase(lines.begin() + pos);
            core->shape_render.RemoveLineFromRender(line);
            core->shape_render.UpdateShapeData();
            DeleteWithIndexFromManagements(LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L, pos);
            for (auto& [type, index] : managements) {
                if (type == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L && index > pos) {
                    --index;
                }
            }
            return true;
        }
        ++pos;
    }
    return false;
}

bool LDDrift::Scene::DeleteCircleShape(const std::string& name) {
    long int pos = 0;
    for (const auto& [circleName, circle,Render] : circleShapes) {
        if (circleName == name) {
            circleShapes.erase(circleShapes.begin() + pos);
            core->shape_render.RemoveShapeFromRender(circle);
            core->shape_render.UpdateShapeData();
            DeleteWithIndexFromManagements(LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C, pos);
            for (auto& [searchInVector, index] : managements) {
                if (searchInVector == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C &&
                    index > pos) { --index; }
            }
            return true;
        }
        ++pos;
    }
    return false;
}

std::pmr::vector<std::string> LDDrift::Scene::GetCircleNames() const {
    std::pmr::vector<std::string> circleNames;
    for (const auto& [circleName, circle,Render] : circleShapes) {
        circleNames.push_back(circleName);
    }
    return circleNames;
}

std::pmr::vector<std::string> LDDrift::Scene::GetPolygonNames() const {
    std::pmr::vector<std::string> polygonNames;
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        polygonNames.push_back(polygonName);
    }
    return polygonNames;
}

std::pmr::vector<std::string> LDDrift::Scene::GetLineNames() const {
    std::pmr::vector<std::string> lineNames;
    for (const auto& [lineName, line,Render] : lines) {
        lineNames.push_back(lineName);
    }
    return lineNames;
}

std::pmr::vector<LDDrift::Actors::Circle*> LDDrift::Scene::GetCircles_ptr() const {
    std::pmr::vector<LDDrift::Actors::Circle*> circles;
    for (const auto& [circleName, circle,Render] : circleShapes) {
        circles.push_back(circle);
    }
    return circles;
}

std::pmr::vector<LDDrift::Actors::Polygon*> LDDrift::Scene::GetPolygons_ptr() const {
    std::pmr::vector<LDDrift::Actors::Polygon*> polygons;
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        polygons.push_back(polygon);
    }
    return polygons;
}

std::pmr::vector<LDDrift::Actors::Line*> LDDrift::Scene::GetLines_ptr() const {
    std::pmr::vector<LDDrift::Actors::Line*> Lines;
    for (const auto& [lineName, line,Render] : lines) {
        Lines.push_back(line);
    }
    return Lines;
}

std::pmr::vector<LDDrift::Actors::Texture*> LDDrift::Scene::GetTextures_Ptr() const {
    std::pmr::vector<LDDrift::Actors::Texture*> r; // result
    for (const auto& [textureName, texture,Render] : textures) {
        r.push_back(texture);
    }
    return r;
}

std::pmr::vector<std::string> LDDrift::Scene::GetTextureNames() const {
    std::pmr::vector<std::string> r; // result
    for (const auto& [textureName, texture,Render] : textures) {
        r.push_back(textureName);
    }
    return r;
}

int LDDrift::Scene::FindTextureWithName(const std::string& name) const {
    int counter = 0;
    for (const auto& [textureName, texture, Render] : textures) {
        if (textureName == name) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

LDDrift::Actors::Texture* LDDrift::Scene::GetTexture(const std::string& name) const {
    for (const auto& [textureName, texture, Render] : textures) {
        if (textureName == name) {
            return texture;
        }
    }
    return nullptr;
}

void LDDrift::Scene::CreateTexture(const std::string& name, const std::filesystem::path& TexturePath,
                                   const std::pmr::vector<float>& vertices) {
    const TEXTURE_INFORMATION newTexture{.textureName = name, .texture = new LDDrift::Actors::Texture(), .render = true};
    newTexture.texture->image_reader.LoadImage(TexturePath);
    newTexture.texture->SetTextureCoordinates(vertices);
    texture_render->AddTexture(newTexture.texture, 1);
    texture_render->SendToGPU();
    textures.push_back(newTexture);
    managements.push_back(QueueManagement{
        .searchInVector = LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_T, .index = textures.size() - 1
    });
    newTexture.texture->GenerateTexture();
    newTexture.texture->image_reader.FreeImage();
}

void LDDrift::Scene::DeleteTexture(const std::string& name) {
    if (const int find = FindTextureWithName(name);
        CheckFindStatus(find)) {
        textures.erase(textures.begin() + find);
        DeleteWithIndexFromManagements(LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_T, find);
        for (auto& [type, index] : managements) {
            if (type == LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_T && index > find) {
                --index;
            }
        }
    }
}

void LDDrift::Scene::SetTextureRendererPTR(LDDrift::TextureRender* texturePTR) {
    texture_render = texturePTR;
}

void LDDrift::Scene::SetChangeColorFunction(const GetAnimationProgressFunction& function) {
    func = function;
}

void LDDrift::Scene::ChangeColorCirclesToBlack() const {
    const std::size_t circleCount = circle_colors.size();
    for (std::size_t circle = 0; circle < circleCount; ++circle) {
        LDDrift::Actors::Circle* circlePtr = circle_colors[circle].first;
        const std::size_t pointCountOfCircle = circlePtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfCircle; ++pointNumber) {
            const LDDrift::VecCol newColor = circle_colors[circle].second[pointNumber] * (static_cast<float>(1 -
                func()));
            circlePtr->SetPointColor(pointNumber, newColor);
        }
    }
}

void LDDrift::Scene::ChangeColorPolygonsToBlack() const {
    const std::size_t polygonCount = polygon_colors.size();
    for (std::size_t polygon = 0; polygon < polygonCount; ++polygon) {
        LDDrift::Actors::Polygon* polygonPtr = polygon_colors[polygon].first;
        const std::size_t pointCountOfPolygon = polygonPtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfPolygon; ++pointNumber) {
            polygonPtr->SetPointColor(pointNumber,
                                      (polygon_colors[polygon].second[pointNumber] * (static_cast<float>(1 - func()))));
        }
    }
}

void LDDrift::Scene::ChangeColorLinesToBlack() const {
    const std::size_t lineCount = line_colors.size();
    for (std::size_t lineNumber = 0; lineNumber < lineCount; ++lineNumber) {
        LDDrift::Actors::Line* linePtr = line_colors[lineNumber].first;
        linePtr->SetLineColor(line_colors[lineNumber].second * (static_cast<float>(1 - func())));
    }
}

void LDDrift::Scene::ChangeColorTexturesToBlack() const {
    const std::size_t textureCount = texture_multipliers.size();
    for (std::size_t textureNumber = 0; textureNumber < textureCount; ++textureNumber) {
        LDDrift::Actors::Texture* texturePtr = texture_multipliers[textureNumber].first;
        texturePtr->SetColorMultiplierForTexture(static_cast<float>(1.0f - func()));
    }
}

void LDDrift::Scene::ChangeColorShapesToBlack() {
    if (func == nullptr) {
        return;
    }
    if (!hasData) {
        hasData = true;
        for (const auto& circle : circleShapes) {
            circle_colors.emplace_back(circle.circle, circle.circle->GetColorOfPoints());
        }
        for (const auto& polygon : polygonShapes) {
            polygon_colors.emplace_back(polygon.polygon, polygon.polygon->GetColorOfPoints());
        }
        for (const auto& line : lines) {
            line_colors.emplace_back(line.line, line.line->GetColor());
        }
        for (const auto& text : textures) {
            texture_multipliers.emplace_back(text.texture, text.texture->GetColorMultiplierOfTexture());
        }
    }
    ChangeColorCirclesToBlack();
    ChangeColorPolygonsToBlack();
    ChangeColorLinesToBlack();
    ChangeColorTexturesToBlack();
}

void LDDrift::Scene::ChangeColorCirclesToMainColor() const {
    const std::size_t circleCount = circle_colors.size();
    for (std::size_t _circle = 0; _circle < circleCount; ++_circle) {
        LDDrift::Actors::Circle* circlePtr = circle_colors[_circle].first;
        const std::size_t pointCountOfCircle = circlePtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfCircle; ++pointNumber) {
            circlePtr->SetPointColor(pointNumber,
                                     circle_colors[_circle].second[pointNumber] * static_cast<float>(func()));
        }
    }
}

void LDDrift::Scene::ChangeColorPolygonsToMainColor() const {
    const std::size_t polygonCount = polygon_colors.size();
    for (std::size_t _polygon = 0; _polygon < polygonCount; ++_polygon) {
        LDDrift::Actors::Polygon* polygonPtr = polygon_colors[_polygon].first;
        const std::size_t pointCountOfPolygon = polygonPtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfPolygon; ++pointNumber) {
            polygonPtr->SetPointColor(pointNumber,
                                      polygon_colors[_polygon].second[pointNumber] * static_cast<float>(func()));
        }
    }
}

void LDDrift::Scene::ChangeColorLinesToMainColor() const {
    const std::size_t lineCount = line_colors.size();
    for (std::size_t _line = 0; _line < lineCount; ++_line) {
        LDDrift::Actors::Line* linePtr = line_colors[_line].first;
        linePtr->SetLineColor(line_colors[_line].second * static_cast<float>(func()));
    }
}

void LDDrift::Scene::ChangeColorTexturesToMainColor() const {
    const std::size_t textureCount = texture_multipliers.size();
    for (std::size_t textureNumber = 0; textureNumber < textureCount; ++textureNumber) {
        LDDrift::Actors::Texture* texturePtr = texture_multipliers[textureNumber].first;
        texturePtr->SetColorMultiplierForTexture(static_cast<float>(func()));
    }
}

void LDDrift::Scene::ChangeColorShapesFromBlackToMainColor() {
    if (func == nullptr) {
        return;
    }
    if (!hasData) {
        hasData = true;
        for (const auto& circle : circleShapes) {
            circle_colors.emplace_back(circle.circle, circle.circle->GetColorOfPoints());
        }
        for (const auto& polygon : polygonShapes) {
            polygon_colors.emplace_back(polygon.polygon, polygon.polygon->GetColorOfPoints());
        }
        for (const auto& line : lines) {
            line_colors.emplace_back(line.line, line.line->GetColor());
        }
        for (const auto& texture : textures) {
            texture_multipliers.emplace_back(texture.texture, texture.texture->GetColorMultiplierOfTexture());
        }
    }

    ChangeColorCirclesToMainColor();
    ChangeColorPolygonsToMainColor();
    ChangeColorLinesToMainColor();
    ChangeColorTexturesToMainColor();
}

void LDDrift::Scene::SetSceneBackground(const std::filesystem::path& path) {
    backgroundTexture.FreeTexture();
    backgroundTexture.image_reader.LoadImage(path);
    backgroundTexture.SetTextureCoordinates(std::pmr::vector<float>{
        //position      tex coord
        -1, 1, 0, 1,
        1, 1, 1, 1,
        1, -1, 1, 0,
        -1, -1, 0, 0
    });
    backgroundTexture.SetColorMultiplierForTexture(1);
    texture_render->AddTexture(&backgroundTexture, 0);
    texture_render->SendToGPU();
}

void LDDrift::Scene::DeleteWithIndexFromManagements(const char type, const std::size_t index) {
    const QueueManagement temp{.searchInVector = type, .index = index};
    if (const auto it = std::ranges::find_if(managements, [temp](const auto& management)
        {
            return management.searchInVector == temp.searchInVector && management.index == temp.index;
        });
        it != managements.end()) {
        managements.erase(it);
    }
}
