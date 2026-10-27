#include "WR_SettingSystem.h"

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

void LDDrift::WR_SettingSystem::saveCircleActor() const {
    std::ofstream jsonOut((settingFolderPath / settingFilename).string(), std::ios::out);
    COF_assert(jsonOut)
    json data;
    for (const auto& [circleName, circle] : core->userProjectSetting.circles) {
        data[ACTOR][CIRCLE][circleName]["radius"] = circle->GetRadius();
        data[ACTOR][CIRCLE][circleName]["point_count"] = circle->GetPointCount();
        data[ACTOR][CIRCLE][circleName]["point_positions"] = ConvertPointsToFloats(circle->GetGlobalPoints());
        data[ACTOR][CIRCLE][circleName]["color"] = ConvertPointColorsToFloats(circle->GetColorOfPoints());
        data[ACTOR][CIRCLE][circleName]["original_point_position"] =
            Convert_Point_ToVector(circle->GetOriginalPosition_global());
        data[ACTOR][CIRCLE][circleName]["speed"] = circle->GetSpeed();
        data[ACTOR][CIRCLE][circleName]["center_pos"] = Convert_Point_ToVector(circle->GetCirclePosition());
        data[ACTOR][CIRCLE][circleName]["thickness"] = circle->GetThickness();
    }
    jsonOut << data;
}

void LDDrift::WR_SettingSystem::savePolygonActor() {
    std::ofstream jsonOut((settingFolderPath / settingFilename).string(), std::ios::out);
    COF_assert(jsonOut)
    json data;
    for (const auto& [polyName, polygon] : core->userProjectSetting.polygons) {
        data[ACTOR][POLYGON][polyName]["thickness"] = polygon->GetThickness();
        data[ACTOR][POLYGON][polyName]["join_line_type"] = ConvertLineJoiningAlgorithmToString(polygon->GetJoinLineAlgorithm().value());
        data[ACTOR][POLYGON][polyName]["point_count"] = polygon->GetPointCount();
        data[ACTOR][POLYGON][polyName]["point_positions"] = ConvertPointsToFloats(polygon->GetGlobalPoints());
        data[ACTOR][POLYGON][polyName]["point_colors"] = ConvertPointColorsToFloats(polygon->GetColorOfPoints());
        data[ACTOR][POLYGON][polyName]["original_point_position"] = Convert_Point_ToVector(polygon->GetOriginalPosition_global());
    }
    jsonOut << data;
}

void LDDrift::WR_SettingSystem::saveLinesActor() {

}

void LDDrift::WR_SettingSystem::saveActors() {
    //saveCircleActor();
    //savePolygonActor();
    //saveLinesActor();
}

void LDDrift::WR_SettingSystem::WriteSettingsOfUserProject() {
    //saveCircleActor();
}
