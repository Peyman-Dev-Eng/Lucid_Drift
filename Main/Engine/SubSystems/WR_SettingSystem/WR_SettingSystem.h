#ifndef LUCID_DRIFT_WR_SETTING_SYSTEM_H
#define LUCID_DRIFT_WR_SETTING_SYSTEM_H
#include <ProjectWatchTower.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
#include <Actors/Line/Line.h>
#include <System/Scene/Scene.h>
#include <nlohmann/json.hpp>
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
        void SetSettings(LDDrift::Core* core);
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
        void saveCircleActor();
        //void savePolygonActor();
        //void saveLinesActor();
        void saveActors();
    public:
        WR_SettingSystem();
        ~WR_SettingSystem();
        void SetCore_PTR(LDDrift::Core* core_ptr);
        void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        void Init();
        void CreateSettingFolder();
        void WriteSettingsOfUserProject();
        void ReadSettingsOfUserProject();
    };
}

#endif
