#include "Compile.h"


namespace
{
    std::string QuotePath(const std::filesystem::path& path) {
        const std::string PATH = path.string();

#ifdef _WIN32
        return "\"" + PATH + "\"";
#elifdef __linux__
        std::string result = "'";

        for (const char ch : PATH) {
            if (ch == '\'')
                result += "'\\''";
            else
                result += ch;
        }

        result += '\'';
        return result;
#endif
    }
}

LDDrift::Compile::Compile() = default;

LDDrift::Compile::Compile(std::filesystem::path&& projectPath, std::filesystem::path&& engineRoot) {
    _projectPath = std::move(projectPath);
    _engineRoot = std::move(engineRoot);
    compilationDirectory = projectPath / "BUILD" / "cmake";
    outputDirectory = projectPath / "BUILD";
}

void LDDrift::Compile::init(std::filesystem::path&& projectPath, std::filesystem::path&& engineRoot) {
    _projectPath = std::move(projectPath);
    _engineRoot = std::move(engineRoot);
    compilationDirectory = projectPath / "BUILD" / "cmake";
    outputDirectory = projectPath / "BUILD";
}

bool LDDrift::Compile::BuildProject() const {
    const auto cmakeFile = _projectPath / "CMakeLists.txt";
    const auto engineCmakeFile = _engineRoot / "Main" / "CMakeLists.txt";

    if (!std::filesystem::is_regular_file(cmakeFile)) {
        std::cerr << "Error: User CMakeLists.txt was not found: "
            << cmakeFile << '\n';
        return false;
    }

    if (!std::filesystem::is_regular_file(engineCmakeFile)) {
        std::cerr << "Error: Lucid_Drift engine CMakeLists.txt was not found: "
            << engineCmakeFile << '\n';
        return false;
    }

    try {
        std::filesystem::create_directories(compilationDirectory);
        std::filesystem::create_directories(outputDirectory);
    } catch (const std::filesystem::filesystem_error& error) {
        std::cerr << "Error creating build directories: "
            << error.what() << '\n';
        return false;
    }

    // Step 1: Configure the user's CMake project.
    const std::string configureCommand =
        "cmake -S " + QuotePath(_projectPath) +
        " -B " + QuotePath(compilationDirectory) +
        " -DLUCID_DRIFT_ROOT=" + QuotePath(_engineRoot) +
        " -DCMAKE_BUILD_TYPE=Release";

    std::cout << "Configuring user project with CMake...\n";

    if (std::system(configureCommand.c_str()) != 0) {
        std::cerr << "Error: CMake configuration failed.\n";
        return false;
    }

    // Step 2: Build the shared library target.
    const std::string buildCommand =
        "cmake --build " + QuotePath(compilationDirectory) +
        " --config Release"
        " --target LucidDriftUserScript"
        " --parallel";

    std::cout << "Building user shared library...\n";

    if (std::system(buildCommand.c_str()) != 0) {
        std::cerr << "Error: User project compilation failed.\n";
        return false;
    }

    const auto outputFile = GetOutputLibraryFile();

    if (!std::filesystem::is_regular_file(outputFile)) {
        std::cerr << "Error: Build succeeded but the output library "
            "was not found: "
            << outputFile << '\n';
        return false;
    }

    std::cout << "User shared library created: "
        << outputFile << '\n';

    return true;
}

std::filesystem::path LDDrift::Compile::GetOutputLibraryFile() const {
#ifdef _WIN32
    constexpr const char* extension = ".dll";
#else
    constexpr const char* extension = ".so";
#endif

    return outputDirectory
        / (_projectPath.filename().string() + extension);
}

LDDrift::Compile::~Compile() = default;
