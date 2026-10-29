#ifndef LUCID_DRIFT_WR_SETTING_SYSTEM_H
#define LUCID_DRIFT_WR_SETTING_SYSTEM_H
#include <ProjectWatchTower.h>
#include <unordered_map>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <System/Scene/Scene.h>
#include <nlohmann/json.hpp>
#define ACTOR "actor"
#define CIRCLE "circle"
#define LINE "line"
#define POLYGON "polygon"
#define KEY_TARGETS "key_targets"
using json = nlohmann::json;

namespace LDDrift
{
    class UserProjectSetting final
    {
    public: // variables
        std::vector<std::string> key_targets;
        std::vector<LDDrift::Scene::CIRCLE_SHAPE_INFORMATION> circles;
        std::vector<LDDrift::Scene::POLYGON_SHAPE_INFORMATION> polygons;
        std::vector<LDDrift::Scene::LINE_ACTOR_INFORMATION> lines;

    public:
        UserProjectSetting();
        ~UserProjectSetting();
        void SetSettings(const LDDrift::Core* core);
    };

    class WR_SettingSystem final
    {
    private:
        std::filesystem::path settingFolderPath;
        std::string settingFilename;
        std::string settingFolderName;
        LDDrift::Core* core;
        LDDrift::ProjectWatchTower* project_watch_tower;

    private:
        static std::vector<float> ConvertPointsToFloats(const std::vector<LDDrift::VecPos2D>& points);
        static std::vector<float> ConvertPointColorsToFloats(const std::vector<LDDrift::VecCol>& colors);
        static std::vector<LDDrift::VecPos2D> ConvertFloatsToVectors(const std::vector<float>& points);
        static std::vector<LDDrift::VecCol> ConvertFloatColorsToVectors(const std::vector<float>& points);
        static std::vector<float> Convert_Point_ToVector(const LDDrift::VecPos2D& point);
        static LDDrift::VecPos2D Convert_Vector_To_Point(const std::vector<float>& vector);
        void saveCircleActor(json& j) const;
        void savePolygonActor(json& j) const;
        void saveLinesActor(json& j) const;
        static std::string ConvertLineJoiningAlgorithmToString(const LDDrift::JoinLineType& jlt);
        static LDDrift::JoinLineType ConvertStringToLineJoiningAlgorithm(const std::string& _st);
        static std::vector<float> ConvertColorToVector(const LDDrift::VecCol& color);
        static int Convert_JLT_ToInteger(const LDDrift::JoinLineType& jlt);

    public:
        WR_SettingSystem();
        ~WR_SettingSystem();
        void SetCore_PTR(LDDrift::Core* core_ptr);
        void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        void Init();
        void CreateSettingFolder();
        void WriteSettingsOfUserProject() const;
        void ReadSettingsOfUserProject() const;
    };
}

#endif
