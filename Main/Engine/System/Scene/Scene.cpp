#include "Scene.h"
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

    for (auto& [circleName, circle,Render] : circleShapes) {
        if (Render) shape_render->AddShapeToRender(circle);
    }
    for (auto& [polygonName, polygon,Render] : polygonShapes) {
        if (Render) shape_render->AddShapeToRender(polygon);
    }
    for (auto& [lineName, line,Render] : lines) {
        if (Render) shape_render->AddLineToRender(line);
    }
    shape_render->UpdateShapeData();
    shape_render->SendDataToGPU();
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
    const CIRCLE_SHAPE_INFORMATION newCircle{.circleName = name, .circle = new LDDrift::Actors::Circle()};
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
    const POLYGON_SHAPE_INFORMATION newPolygon{.polygonName = name, .polygon = new LDDrift::Actors::Polygon()};
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
            {static_cast<float>(endPos[0]), static_cast<float>(endPos[1])})
    };
    newLine.line->SetScreenSize(core->window.GetViewportSize());
    newLine.line->SetThickness(static_cast<float>(_thickness));
    newLine.line->SetLineColor(color);
    newLine.line->CreateTriangles();
    lines.push_back({.lineName = newLine.lineName, .line = newLine.line});
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
                                        const std::vector<LDDrift::VecCol>& colors, const float thickness,
                                        const int joinLine_A) {
    const POLYGON_SHAPE_INFORMATION newPolygon{.polygonName = name, .polygon = new LDDrift::Actors::Polygon()};
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
            return true;
        }
        ++pos;
    }
    return false;
}

std::vector<std::string> LDDrift::Scene::GetCircleNames() const {
    std::vector<std::string> circleNames;
    for (const auto& [circleName, circle,Render] : circleShapes) {
        circleNames.push_back(circleName);
    }
    return circleNames;
}

std::vector<std::string> LDDrift::Scene::GetPolygonNames() const {
    std::vector<std::string> polygonNames;
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        polygonNames.push_back(polygonName);
    }
    return polygonNames;
}

std::vector<std::string> LDDrift::Scene::GetLineNames() const {
    std::vector<std::string> lineNames;
    for (const auto& [lineName, line,Render] : lines) {
        lineNames.push_back(lineName);
    }
    return lineNames;
}

std::vector<LDDrift::Actors::Circle*> LDDrift::Scene::GetCircles_ptr() const {
    std::vector<LDDrift::Actors::Circle*> circles;
    for (const auto& [circleName, circle,Render] : circleShapes) {
        circles.push_back(circle);
    }
    return circles;
}

std::vector<LDDrift::Actors::Polygon*> LDDrift::Scene::GetPolygons_ptr() const {
    std::vector<LDDrift::Actors::Polygon*> polygons;
    for (const auto& [polygonName, polygon,Render] : polygonShapes) {
        polygons.push_back(polygon);
    }
    return polygons;
}

std::vector<LDDrift::Actors::Line*> LDDrift::Scene::GetLines_ptr() const {
    std::vector<LDDrift::Actors::Line*> Lines;
    for (const auto& [lineName, line,Render] : lines) {
        Lines.push_back(line);
    }
    return Lines;
}

std::vector<LDDrift::Texture*> LDDrift::Scene::GetTextures_Ptr() const {
    std::vector<LDDrift::Texture*> r; // result
    for (const auto& [textureName, texture,Render] : textures) {
        r.push_back(texture);
    }
    return r;
}

std::vector<std::string> LDDrift::Scene::GetTextureNames() const {
    std::vector<std::string> r; // result
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

LDDrift::Texture* LDDrift::Scene::GetTexture(const std::string& name) const {
    for (const auto& [textureName, texture, Render] : textures) {
        if (textureName == name) {
            return texture;
        }
    }
    return nullptr;
}

void LDDrift::Scene::CreateTexture(const std::string& name, const std::filesystem::path& TexturePath,
                                   const unsigned short int desired_chan, const std::vector<float>& vertices) {
    const TEXTURE_INFORMATION newTexture{.textureName = name, .texture = new LDDrift::Texture()};
    newTexture.texture->image_reader.LoadImage(TexturePath);
    newTexture.texture->SetTextureCoordinates(vertices);
    texture_render->AddTexture(newTexture.texture);
    texture_render->SendToGPU();
    textures.push_back(newTexture);
}

void LDDrift::Scene::DeleteTexture(const std::string& name) {
    if (const int find = FindTextureWithName(name);
        CheckFindStatus(find)) {
        textures.erase(textures.begin() + find);
    }
}

void LDDrift::Scene::SetTextureRendererPTR(LDDrift::TextureRender* texturePTR) {
    texture_render = texturePTR;
}

void LDDrift::Scene::SetChangeColorFunction(const GetAnimationProgressFunction function) {
    func = function;
}

void LDDrift::Scene::freeThreadsOfA_Group() {
    if (A_CC_Circle_TB.joinable()) {
        A_CC_Circle_TB.join();
    }
    if (A_CC_Line_TB.joinable()) {
        A_CC_Line_TB.join();
    }
    if (A_CC_Polygon_TB.joinable()) {
        A_CC_Polygon_TB.join();
    }
    if (A_CC_Texture_TB.joinable()) {
        A_CC_Texture_TB.join();
    }
}

void LDDrift::Scene::freeThreadsOfB_Group() {
    if (B_CC_Circle_FB_TMC.joinable()) {
        B_CC_Circle_FB_TMC.join();
    }
    if (B_CC_Line_FB_TMC.joinable()) {
        B_CC_Line_FB_TMC.join();
    }
    if (B_CC_Polygon_FB_TMC.joinable()) {
        B_CC_Polygon_FB_TMC.join();
    }
    if (B_CC_Texture_FB_TMC.joinable()) {
        B_CC_Texture_FB_TMC.join();
    }
}

void LDDrift::Scene::freeThreads() {
    freeThreadsOfA_Group();
    freeThreadsOfB_Group();
}

void LDDrift::Scene::ChangeColorCirclesToBlack() const {
    const std::size_t circleCount = circleShapes.size();
    for (std::size_t circle = 0; circle < circleCount; ++circle) {
        LDDrift::Actors::Circle* circlePtr = circleShapes[circle].circle;
        const std::size_t pointCountOfCircle = circlePtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfCircle; ++pointNumber) {
            const LDDrift::VecCol newColor = circlePtr->GetPointColor(pointNumber) * (static_cast<float>(1 - func()));
            circlePtr->SetPointColor(pointNumber, newColor);
        }
    }
}

void LDDrift::Scene::ChangeColorPolygonsToBlack() const {
    const std::size_t polygonCount = polygonShapes.size();
    for (std::size_t polygon = 0; polygon < polygonCount; ++polygon) {
        LDDrift::Actors::Polygon* polygonPtr = polygonShapes[polygon].polygon;
        const std::size_t pointCountOfPolygon = polygonPtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfPolygon; ++pointNumber) {
            polygonPtr->SetPointColor(pointNumber,
                                      (polygonPtr->GetPointColor(pointNumber) * (static_cast<float>(1 - func()))));
        }
    }
}

void LDDrift::Scene::ChangeColorLinesToBlack() const {
    const std::size_t lineCount = lines.size();
    for (std::size_t lineNumber = 0; lineNumber < lineCount; ++lineNumber) {
        LDDrift::Actors::Line* linePtr = lines[lineNumber].line;
        linePtr->SetLineColor(linePtr->GetColor() * (static_cast<float>(1 - func())));
    }
}

void LDDrift::Scene::ChangeColorTexturesToBlack() const {
    const std::size_t textureCount = textures.size();
    for (std::size_t textureNumber = 0; textureNumber < textureCount; ++textureNumber) {
        LDDrift::Texture* texturePtr = textures[textureNumber].texture;
        texturePtr->SetColorMultiplierForTexture(static_cast<float>(1.0f - func()));
    }
}

void LDDrift::Scene::ChangeColorShapesToBlack() {
    if (func == nullptr) {
        return;
    }
    A_CC_Circle_TB = std::thread([this]() { ChangeColorCirclesToBlack(); });

    A_CC_Polygon_TB = std::thread([this]() { ChangeColorPolygonsToBlack(); });

    A_CC_Line_TB = std::thread([this]() { ChangeColorLinesToBlack(); });

    A_CC_Texture_TB = std::thread([this]() { ChangeColorTexturesToBlack(); });

    freeThreadsOfA_Group();
}

void LDDrift::Scene::ChangeColorCirclesToMainColor() const {
    const std::size_t circleCount = circleShapes.size();
    for (std::size_t circle = 0; circle < circleCount; ++circle) {
        LDDrift::Actors::Circle* circlePtr = circleShapes[circle].circle;
        const std::size_t pointCountOfCircle = circlePtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfCircle; ++pointNumber) {
            circlePtr->SetPointColor(pointNumber, circlePtr->GetPointColor(pointNumber) * static_cast<float>(func()));
        }
    }
}

void LDDrift::Scene::ChangeColorPolygonsToMainColor() const {
    const std::size_t polygonCount = polygonShapes.size();
    for (std::size_t polygon = 0; polygon < polygonCount; ++polygon) {
        LDDrift::Actors::Polygon* polygonPtr = polygonShapes[polygon].polygon;
        const std::size_t pointCountOfPolygon = polygonPtr->GetPointCount();
        for (std::size_t pointNumber = 0; pointNumber < pointCountOfPolygon; ++pointNumber) {
            polygonPtr->SetPointColor(pointNumber, polygonPtr->GetPointColor(pointNumber) * static_cast<float>(func()));
        }
    }
}

void LDDrift::Scene::ChangeColorLinesToMainColor() const {
    const std::size_t lineCount = lines.size();
    for (std::size_t line = 0; line < lineCount; ++line) {
        LDDrift::Actors::Line* linePtr = lines[line].line;
        linePtr->SetLineColor(linePtr->GetColor() * static_cast<float>(func()));
    }
}

void LDDrift::Scene::ChangeColorTexturesToMainColor() const {
    const std::size_t textureCount = textures.size();
    for (std::size_t textureNumber = 0; textureNumber < textureCount; ++textureNumber) {
        LDDrift::Texture* texturePtr = textures[textureNumber].texture;
        texturePtr->SetColorMultiplierForTexture(static_cast<float>(func()));
    }
}

void LDDrift::Scene::ChangeColorShapesFromBlackToMainColor() {
    if (func == nullptr) {
        return;
    }
    B_CC_Circle_FB_TMC = std::thread([this]() { ChangeColorCirclesToMainColor(); });

    B_CC_Polygon_FB_TMC = std::thread([this]() { ChangeColorPolygonsToMainColor(); });

    B_CC_Line_FB_TMC = std::thread([this]() { ChangeColorLinesToMainColor(); });

    B_CC_Texture_FB_TMC = std::thread([this]() { ChangeColorTexturesToMainColor(); });

    freeThreadsOfB_Group();
}
