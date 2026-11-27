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

#ifndef LUCID_DRIFT_WR_SETTING_SYSTEM_H
#define LUCID_DRIFT_WR_SETTING_SYSTEM_H
#include <ProjectWatchTower.h>
#include <unordered_map>
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
    namespace Actors
    {
        class Shape;
        class Polygon;
        class Circle;
        class Line;
    }
    class Core;

    class UserProjectSetting final
    {
    public: // variables
        std::pmr::vector<std::string> key_targets;
        std::pmr::vector<std::pair<std::string, LDDrift::Scene*>> Scenes;

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
        static std::pmr::vector<float> ConvertPointsToFloats(const std::pmr::vector<LDDrift::VecPos2D>& points);
        static std::pmr::vector<float> ConvertPointColorsToFloats(const std::pmr::vector<LDDrift::VecCol>& colors);
        static std::pmr::vector<LDDrift::VecPos2D> ConvertFloatsToVectors(const std::pmr::vector<float>& points);
        static std::pmr::vector<LDDrift::VecCol> ConvertFloatColorsToVectors(const std::pmr::vector<float>& points);
        static std::pmr::vector<float> Convert_Point_ToVector(const LDDrift::VecPos2D& point);
        static LDDrift::VecPos2D Convert_Vector_To_Point(const std::pmr::vector<float>& vector);
        void saveKeyTargetsOfKeyboard(json& j) const;
        void saveScenes(json& j);
        static std::string ConvertLineJoiningAlgorithmToString(const LDDrift::JoinLineType& jlt);
        static LDDrift::JoinLineType ConvertStringToLineJoiningAlgorithm(const std::string& _st);
        static std::pmr::vector<float> ConvertColorToVector(const LDDrift::VecCol& color);
        static int Convert_JLT_ToInteger(const LDDrift::JoinLineType& jlt);

    public:
        WR_SettingSystem();
        ~WR_SettingSystem();
        void SetCore_PTR(LDDrift::Core* core_ptr);
        void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        void CreateSettingFolder();
        void WriteSettingsOfUserProject() const;
        void ReadSettingsOfUserProject() const;
    };
}

#endif
