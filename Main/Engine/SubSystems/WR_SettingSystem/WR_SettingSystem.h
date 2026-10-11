#ifndef LUCID_DRIFT_WR_SETTING_SYSTEM_H
#define LUCID_DRIFT_WR_SETTING_SYSTEM_H
#include <ProjectWatchTower.h>

namespace LDDrift
{
    class WR_SettingSystem
    {
    private:
        LDDrift::ProjectWatchTower* project_watch_tower;
    public:
        WR_SettingSystem();
        ~WR_SettingSystem();
        void SetProjectWatchTowerPTR(LDDrift::ProjectWatchTower* projectWatchTowerPTR);
    };
}

#endif
