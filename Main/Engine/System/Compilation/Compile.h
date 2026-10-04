#ifndef LUCID_DRIFT_COMPILE_H
#define LUCID_DRIFT_COMPILE_H
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace LDDrift
{
    class Compile final
    {
    private:
        std::vector<std::filesystem::path> pathFilesToCompile;
        std::string objectFileName;
        std::filesystem::path objectFilePath;
        std::filesystem::path compilationDirectory;
    public:
        Compile();
        void CreateCompilationDirectory();
        ~Compile();
    };
}

#endif
