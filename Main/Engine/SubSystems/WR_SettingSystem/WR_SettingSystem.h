#ifndef LUCID_DRIFT_WR_SETTING_SYSTEM_H
#define LUCID_DRIFT_WR_SETTING_SYSTEM_H
#include <ProjectWatchTower.h>

namespace LDDrift
{
    class SettingUserProject
    {
    private:
        std::vector<std::string> KeyTargets;
    };

    class WR_SettingSystem
    {
    private:
        const std::string SettingFolderName = "ProjectSetting";
        std::filesystem::path SettingFolderPath;
        LDDrift::ProjectWatchTower* project_watch_tower;

    public:
        WR_SettingSystem();
        ~WR_SettingSystem();
        void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
        void Init();
        void CreateSettingFolder();
        void WriteSettingsOfUserProject();
        void ReadSettingsOfUserProject();
    };
}

#endif
