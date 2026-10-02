#ifndef LUCID_DRIFT_GUILOGIC_H
#define LUCID_DRIFT_GUILOGIC_H
#include <GUI.h>
#include <ProjectWatchTower.h>

namespace LDDrift
{
    namespace Anonymous
    {
        inline LDDrift::ProjectWatchTower* projectWatchTowerPTR;
    }

    class GuiLogic
    {
    public:
        static void SetProjectWatchTowerPtr(ProjectWatchTower* projectWatchTowerPtr);
        static LDDrift::GUI::DefaultWindowsData PressEnterInSearchBarInProjectWatchTower(
            LDDrift::GUI::DefaultWindowsData*);
        static void ProjectManagerHandling(LDDrift::GUI::DefaultWindowsData*);
    };
}

#endif
