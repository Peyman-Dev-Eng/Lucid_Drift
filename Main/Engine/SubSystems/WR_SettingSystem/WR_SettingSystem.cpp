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

#include "WR_SettingSystem.h"
#include "Actors/Shapes/MainShape/Shape.h"
#include "Actors/Shapes/Circle/CircleShape.h"
#include "Actors/Shapes/Polygon/Polygon.h"
#include "Actors/Line/Line.h"
#include "System/Core/Core.h"

LDDrift::UserProjectSetting::UserProjectSetting() = default;

LDDrift::UserProjectSetting::~UserProjectSetting() = default;

void LDDrift::UserProjectSetting::SetSettings(const LDDrift::Core* core) {
    for (const auto& [NAME, SCENE] : core->sceneManager.scenes) {
        Scenes.push_back({NAME, SCENE});
    }

    for (const LDDrift::Event::Keyboard::LinuxKeyboardKeyCode& key : LDDrift::TargetKeys) {
        if (const std::string keyName = LDDrift::input::ConvertKeyEnumToString(key);
            keyName != NULL_STRING)
            key_targets.push_back(keyName);
    }
}

LDDrift::WR_SettingSystem::WR_SettingSystem() : settingFolderName("ProjectSetting"), core(nullptr),
                                                project_watch_tower(nullptr) {}

LDDrift::WR_SettingSystem::~WR_SettingSystem() = default;

void LDDrift::WR_SettingSystem::SetCore_PTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::WR_SettingSystem::SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR) {
    project_watch_tower = projectWatchTowerPTR;
}

void LDDrift::WR_SettingSystem::CreateSettingFolder() {
    const std::filesystem::path& buildFolderOfProject_path = project_watch_tower->GetBuildFolderPath();
    settingFolderPath = std::filesystem::path(buildFolderOfProject_path / settingFolderName);
    settingFilename = "user_project_setting.json";
    create_directory(settingFolderPath);
}

std::pmr::vector<float> LDDrift::WR_SettingSystem::ConvertPointsToFloats(const std::pmr::vector<LDDrift::VecPos2D>& points) {
    std::pmr::vector<float> result;
    result.reserve(points.size() * 2);
    for (const LDDrift::VecPos2D& point : points) {
        result.push_back(point.X);
        result.push_back(point.Y);
    }
    return result;
}

std::pmr::vector<float> LDDrift::WR_SettingSystem::ConvertPointColorsToFloats(const std::pmr::vector<LDDrift::VecCol>& colors) {
    std::pmr::vector<float> result;
    result.reserve(colors.size() * 4);
    for (const LDDrift::VecCol& color : colors) {
        result.push_back(color.R);
        result.push_back(color.G);
        result.push_back(color.B);
        result.push_back(color.A);
    }
    return result;
}

std::string LDDrift::WR_SettingSystem::ConvertLineJoiningAlgorithmToString(const LDDrift::JoinLineType& jlt) {
    if (jlt == LDDrift::JoinLineType::Miter) {
        return "Miter";
    } else if (jlt == LDDrift::JoinLineType::Round) {
        return "Round";
    } else if (jlt == LDDrift::JoinLineType::Bevel) {
        return "Bevel";
    } else {
        return NULL_STRING;
    }
}

std::pmr::vector<LDDrift::VecCol> LDDrift::WR_SettingSystem::ConvertFloatColorsToVectors(const std::pmr::vector<float>& points) {
    std::pmr::vector<LDDrift::VecCol> result;
    result.reserve(points.size() / 4);
    const std::size_t size = points.size() / 4;
    for (std::size_t i = 0; i < size; ++i) {
        result.emplace_back(points[i * 4 + 0], points[i * 4 + 1], points[i * 4 + 2], points[i * 4 + 3]);
    }
    return result;
}

LDDrift::JoinLineType LDDrift::WR_SettingSystem::ConvertStringToLineJoiningAlgorithm(const std::string& _st) {
    if (_st == "Miter") {
        return LDDrift::JoinLineType::Miter;
    } else if (_st == "Round") {
        return LDDrift::JoinLineType::Round;
    } else if (_st == "Bevel") {
        return LDDrift::JoinLineType::Bevel;
    }
    return LDDrift::JoinLineType::Null;
}

std::pmr::vector<LDDrift::VecPos2D> LDDrift::WR_SettingSystem::ConvertFloatsToVectors(const std::pmr::vector<float>& points) {
    std::pmr::vector<LDDrift::VecPos2D> result;
    const std::size_t size = points.size() / 2;
    result.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
        result.emplace_back(points[i * 2 + 0], points[i * 2 + 1]);
    }
    return result;
}

std::pmr::vector<float> LDDrift::WR_SettingSystem::Convert_Point_ToVector(const LDDrift::VecPos2D& point) {
    return std::pmr::vector<float>{point.X, point.Y};
}

LDDrift::VecPos2D LDDrift::WR_SettingSystem::Convert_Vector_To_Point(const std::pmr::vector<float>& vector) {
    return LDDrift::VecPos2D{vector[0], vector[1]};
}

std::pmr::vector<float> LDDrift::WR_SettingSystem::ConvertColorToVector(const LDDrift::VecCol& color) {
    return std::pmr::vector<float>{color.R, color.G, color.B, color.A};
}


void LDDrift::WR_SettingSystem::saveKeyTargetsOfKeyboard(json& j) const {
    j[KEY_TARGETS] = core->userProjectSetting.key_targets;
}

void LDDrift::WR_SettingSystem::saveScenes(json& j) {
    for (const auto& scene : core->userProjectSetting.Scenes) {
        for (const auto& circle : scene.second->circleShapes) {
            j[scene.first][ACTOR][CIRCLE][circle.circleName]["radius"] = circle.circle->GetRadius();
            j[scene.first][ACTOR][CIRCLE][circle.circleName]["speed"] = circle.circle->GetSpeed();
            j[scene.first][ACTOR][CIRCLE][circle.circleName]["center_pos"] = Convert_Point_ToVector(circle.circle->GetCirclePosition());
            j[scene.first][ACTOR][CIRCLE][circle.circleName]["color"] = ConvertColorToVector(circle.circle->GetPointColor(0));
            j[scene.first][ACTOR][CIRCLE][circle.circleName]["thickness"] = circle.circle->GetThickness();

        }
    }
}

void LDDrift::WR_SettingSystem::WriteSettingsOfUserProject() const {
    json _json;
    saveKeyTargetsOfKeyboard(_json);

    std::ofstream out((settingFolderPath / settingFilename).string(), std::ios::out);
    out << _json.dump(4);
}

int LDDrift::WR_SettingSystem::Convert_JLT_ToInteger(const LDDrift::JoinLineType& jlt) {
    if (jlt == LDDrift::JoinLineType::Miter) {
        return MITER;
    } else if (jlt == LDDrift::JoinLineType::Round) {
        return ROUND;
    } else if (jlt == LDDrift::JoinLineType::Bevel) {
        return BEVEL;
    }
    return -1;
}

void LDDrift::WR_SettingSystem::ReadSettingsOfUserProject() const {
    if (std::ifstream input((settingFolderPath / settingFilename).string(), std::ios::in);
        input.fail() == false) {
        json main_json;
        input.seekg(std::ios::beg);
        input >> main_json;

        json circles_json = main_json[ACTOR][CIRCLE];
        json lines_json = main_json[ACTOR][LINE];
        json polygons_json = main_json[ACTOR][POLYGON];
        std::pmr::vector<std::string> key_targets;
        if (main_json.contains(KEY_TARGETS))
            key_targets = main_json[KEY_TARGETS];
        for (const auto& circle : circles_json.items()) {
            // extract data
            // start
            const std::string& name = circle.key();
            const json& value = circle.value();
            const int pointCount = value["point_count"];
            const int radius = value["radius"];
            const int speed = value["speed"];
            const LDDrift::VecPos2D pos = Convert_Vector_To_Point(value["center_pos"]);
            const LDDrift::VecCol col = ConvertFloatColorsToVectors(value["color"])[0];
            const float thick = value["thickness"];
            // end
            core->sceneManager.GetCurrentScene()->CreateCircleShape(name, pointCount, radius, speed, pos, col,
                                                                    thick == 0 ? -1 : thick);
        }

        for (const auto& lines : lines_json.items()) {
            // extract data
            // start
            const std::string& name = lines.key();
            const int thick = lines_json[lines.key()]["thickness"];
            const LDDrift::VecPos2D st_pnt = Convert_Vector_To_Point(lines_json[name]["start_pos"]);
            // start position point
            const LDDrift::VecPos2D ed_pnt = Convert_Vector_To_Point(lines_json[name]["end_pos"]);
            // end position point
            const LDDrift::VecCol col = ConvertFloatColorsToVectors(lines_json[name]["color"])[0];

            const int st[2] = {static_cast<int>(st_pnt.X), static_cast<int>(st_pnt.Y)};
            const int ed[2] = {static_cast<int>(ed_pnt.X), static_cast<int>(ed_pnt.Y)};
            // end
            core->sceneManager.GetCurrentScene()->CreateLineActor(name, thick, st, ed, col);
        }
        for (const auto& polygon : polygons_json.items()) {
            // extract data
            // start
            const std::string& name = polygon.key();
            const json& value = polygon.value();
            const int pointCount = value["point_count"];
            const float thick = value["thickness"];
            const std::pmr::vector<int> points = value["point_positions"];
            const std::pmr::vector<LDDrift::VecCol> colors =
                ConvertFloatColorsToVectors(value["point_colors"]);
            const LDDrift::JoinLineType jlt =
                ConvertStringToLineJoiningAlgorithm(value["join_line_type"]);
            const int speed = value["speed"];
            // end
            core->sceneManager.GetCurrentScene()->CreatePolygonShape(name, pointCount, speed, points.data(), colors,
                                                                     thick,
                                                                     Convert_JLT_ToInteger(jlt));
        }
        for (const std::string& key : key_targets) {
            LDDrift::input::Keyboard::SetKeyTarget(key);
        }
    }
}
