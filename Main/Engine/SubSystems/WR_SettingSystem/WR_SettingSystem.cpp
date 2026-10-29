#include "WR_SettingSystem.h"

#include <typeinfo>

#include "System/Core/Core.h"

LDDrift::UserProjectSetting::UserProjectSetting() = default;

LDDrift::UserProjectSetting::~UserProjectSetting() = default;

void LDDrift::UserProjectSetting::SetSettings(const LDDrift::Core* core) {
    circles = core->scene.circleShapes;
    polygons = core->scene.polygonShapes;
    lines = core->scene.lines;
    for (std::size_t i = 0; i <= 180; ++i) {
        std::string key = LDDrift::input::ConvertKeyEnumToString(
            static_cast<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode>(i));
        if (key != NULL_STRING)
            key_targets.push_back(key);
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

std::vector<float> LDDrift::WR_SettingSystem::ConvertPointsToFloats(const std::vector<LDDrift::VecPos2D>& points) {
    std::vector<float> result;
    result.reserve(points.size() * 2);
    for (const LDDrift::VecPos2D& point : points) {
        result.push_back(point.X);
        result.push_back(point.Y);
    }
    return result;
}

std::vector<float> LDDrift::WR_SettingSystem::ConvertPointColorsToFloats(const std::vector<LDDrift::VecCol>& colors) {
    std::vector<float> result;
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

std::vector<LDDrift::VecCol> LDDrift::WR_SettingSystem::ConvertFloatColorsToVectors(const std::vector<float>& points) {
    std::vector<LDDrift::VecCol> result;
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

std::vector<LDDrift::VecPos2D> LDDrift::WR_SettingSystem::ConvertFloatsToVectors(const std::vector<float>& points) {
    std::vector<LDDrift::VecPos2D> result;
    const std::size_t size = points.size() / 2;
    result.reserve(size);
    for (std::size_t i = 0; i < size; ++i) {
        result.emplace_back(points[i * 2 + 0], points[i * 2 + 1]);
    }
    return result;
}

std::vector<float> LDDrift::WR_SettingSystem::Convert_Point_ToVector(const LDDrift::VecPos2D& point) {
    return std::vector<float>{point.X, point.Y};
}

LDDrift::VecPos2D LDDrift::WR_SettingSystem::Convert_Vector_To_Point(const std::vector<float>& vector) {
    return LDDrift::VecPos2D{vector[0], vector[1]};
}

void LDDrift::WR_SettingSystem::saveCircleActor(json& j) const {
    for (const auto& [circleName, circle] : core->userProjectSetting.circles) {
        j[ACTOR][CIRCLE][circleName]["radius"] = circle->GetRadius();
        j[ACTOR][CIRCLE][circleName]["point_count"] = circle->GetPointCount();
        j[ACTOR][CIRCLE][circleName]["point_positions"] = ConvertPointsToFloats(circle->GetGlobalPoints());
        j[ACTOR][CIRCLE][circleName]["color"] = ConvertPointColorsToFloats(circle->GetColorOfPoints());
        j[ACTOR][CIRCLE][circleName]["original_point_position"] =
            Convert_Point_ToVector(circle->GetOriginalPosition_global());
        j[ACTOR][CIRCLE][circleName]["speed"] = circle->GetSpeed();
        j[ACTOR][CIRCLE][circleName]["center_pos"] = Convert_Point_ToVector(circle->GetCirclePosition());
        j[ACTOR][CIRCLE][circleName]["thickness"] = circle->GetThickness();
    }
}

std::vector<float> LDDrift::WR_SettingSystem::ConvertColorToVector(const LDDrift::VecCol& color) {
    return std::vector<float>{color.R, color.G, color.B, color.A};
}

void LDDrift::WR_SettingSystem::savePolygonActor(json& j) const {
    for (const auto& [polyName, polygon] : core->userProjectSetting.polygons) {
        j[ACTOR][POLYGON][polyName]["thickness"] = polygon->GetThickness();
        j[ACTOR][POLYGON][polyName]["join_line_type"] = ConvertLineJoiningAlgorithmToString(
            polygon->GetJoinLineAlgorithm().value());
        j[ACTOR][POLYGON][polyName]["point_count"] = polygon->GetPointCount();
        j[ACTOR][POLYGON][polyName]["point_positions"] = ConvertPointsToFloats(polygon->GetGlobalPoints());
        j[ACTOR][POLYGON][polyName]["point_colors"] = ConvertPointColorsToFloats(polygon->GetColorOfPoints());
        j[ACTOR][POLYGON][polyName]["original_point_position"] = Convert_Point_ToVector(
            polygon->GetOriginalPosition_global());
        j[ACTOR][POLYGON][polyName]["speed"] = polygon->GetSpeed();
        j[ACTOR][POLYGON][polyName]["shape_type"] = polygon->ShapeIsConcave() ? "concave" : "convex";
    }
}

void LDDrift::WR_SettingSystem::saveLinesActor(json& j) const {
    for (const auto& [lineName, line] : core->userProjectSetting.lines) {
        j[ACTOR][LINE][lineName]["thickness"] = line->GetThickness();
        j[ACTOR][LINE][lineName]["start_pos"] = Convert_Point_ToVector(line->GetFirstPoint());
        j[ACTOR][LINE][lineName]["end_pos"] = Convert_Point_ToVector(line->GetSecondPoint());
        j[ACTOR][LINE][lineName]["color"] = ConvertColorToVector(line->GetColor());
    }
}

void LDDrift::WR_SettingSystem::WriteSettingsOfUserProject() const {
    json _json;
    saveCircleActor(_json);
    savePolygonActor(_json);
    saveLinesActor(_json);

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
            core->scene.CreateCircleShape(name, pointCount, radius, speed, pos, col, thick == 0 ? -1 : thick);
        }

        for (const auto& lines : lines_json.items()) {
            const std::string& name = lines.key();
            const int thick = lines_json[lines.key()]["thickness"];
            const LDDrift::VecPos2D st_pnt = Convert_Vector_To_Point(lines_json[name]["start_pos"]);
            // start position point
            const LDDrift::VecPos2D ed_pnt = Convert_Vector_To_Point(lines_json[name]["end_pos"]);
            const LDDrift::VecCol col = ConvertFloatColorsToVectors(lines_json[name]["color"])[0];

            const int st[2] = {static_cast<int>(st_pnt.X), static_cast<int>(st_pnt.Y)};
            const int ed[2] = {static_cast<int>(ed_pnt.X), static_cast<int>(ed_pnt.Y)};

            core->scene.CreateLineActor(name, thick, st, ed, col);
        }
        for (const auto& polygon : polygons_json.items()) {
            const std::string& name = polygon.key();
            const json& value = polygon.value();
            const int pointCount = value["point_count"];
            const float thick = value["thickness"];
            const std::vector<int> points = value["point_positions"];
            const std::vector<LDDrift::VecCol> colors =
                ConvertFloatColorsToVectors(value["point_colors"]);
            const LDDrift::JoinLineType jlt =
                ConvertStringToLineJoiningAlgorithm(value["join_line_type"]);
            const int speed = value["speed"];
            core->scene.CreatePolygonShape(name, pointCount, speed, points.data(), colors, thick,
                                           Convert_JLT_ToInteger(jlt));
        }
    }
}
