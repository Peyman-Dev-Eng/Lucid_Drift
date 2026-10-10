#ifndef LUCID_DRIFT_COMPILE_H
#define LUCID_DRIFT_COMPILE_H
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <ProjectWatchTower.h>

namespace LDDrift
{
    class Compile
    {
    private:
        LDDrift::ProjectWatchTower* ProjectWatchTowerPTR = nullptr;
        void SetCompilePath(std::string& compileMess) const;
    public:
        Compile();
        void BuildProject();
        ~Compile();
    };
}

#endif
