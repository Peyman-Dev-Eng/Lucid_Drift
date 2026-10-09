#ifndef LUCID_DRIFT_COMPILE_H
#define LUCID_DRIFT_COMPILE_H
#include <filesystem>
#include <iostream>

namespace LDDrift
{
    class Compile
    {
    private:
        std::filesystem::path _projectPath;
        std::filesystem::path _engineRoot;
        std::filesystem::path compilationDirectory;
        std::filesystem::path outputDirectory;
    public:
        Compile();
        Compile(std::filesystem::path&& projectPath, std::filesystem::path&& engineRoot);
        void init(std::filesystem::path&& projectPath, std::filesystem::path&& engineRoot);
        [[nodiscard]] bool BuildProject() const;
        [[nodiscard]] std::filesystem::path GetOutputLibraryFile() const;
        ~Compile();
    };
}

#endif
