#include "GraphicalUserInterfaceWindowHandler.h"
#include <System/Core/Core.h>

void LDDrift::DefaultWindowsData::SetTextPrintInWindow(const std::string& text) {
    std::vector<std::string> result;
    const std::size_t textSize = text.size();
    std::size_t startTextLine = 0;
    std::size_t endTextLine = 0;
    while (endTextLine < textSize) {
        while (endTextLine < textSize && text[endTextLine] != '\n') {
            ++endTextLine;
        }
        result.push_back(text.substr(startTextLine, (endTextLine - startTextLine)));
        if (endTextLine < textSize) {
            ++endTextLine;
        }
        startTextLine = endTextLine;
    }
    textPrintInWindow = std::move(result);
}

///////////// Main /////////////

LDDrift::Main_GraphicalWindow::Main_GraphicalWindow() = default;

LDDrift::Main_GraphicalWindow::~Main_GraphicalWindow() = default;

void LDDrift::Main_GraphicalWindow::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::Main_GraphicalWindow::Initialize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();

    name = MAIN_WINDOW_NAME;
    position = {0, 0};
    size = {350, windowSize.Y / 2};
    Show = true;
    canMoveWindow = false;
    canResizeWindow = false;
    std::memset(searchBuffer, '\0', sizeof(searchBuffer));
    SetTextPrintInWindow("");
}

void LDDrift::Main_GraphicalWindow::Resize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();

    position = {0, 0};
    size = {350, windowSize.Y / 2};
}

void LDDrift::Main_GraphicalWindow::Render() const {
    if (ImGui::Button("Game Setting")) {
        core->gui.OpenWindow(GAME_SETTING_WINDOW_NAME);
    }
    ImGui::Separator();
    if (ImGui::Button("Compile")) {
        core->gui.ProjectWatchTower_PTR->RemoveBuildFile();
        core->gui.CompilePTR->BuildProject();
    }
    ImGui::SameLine();
    static bool initializedShowError = false;
    static std::optional<int> showError; // show error if value of this var equals to ( 1 or one )
    if (initializedShowError == false && !showError.has_value()) {
        initializedShowError = true;
        showError = 0;
    }
    const LDDrift::CompileBuildStatus build = core->gui.CompilePTR->GetStatus();
    if (core->gui.runGame == false) {
        if (ImGui::Button("Run")) {
            if (build == LDDrift::CompileBuildStatus::Succeeded) {
                core->gui.runGame = true;
                LDDrift::EngineAPI::AfterCompileProject();
            }
        }
    } else {
        if (ImGui::Button("Pause")) {
            core->gui.runGame = false;
        }
    }
    ImGui::TextUnformatted("Build Status: ");
    ImGui::SameLine();
    if (build == LDDrift::CompileBuildStatus::Building) {
        ImGui::TextUnformatted("Compiling...");
        showError = 0;
    } else if (build == LDDrift::CompileBuildStatus::Succeeded) {
        ImGui::TextUnformatted("Compiled");
    } else if (build == LDDrift::CompileBuildStatus::Failed) {
        ImGui::TextUnformatted("Failed");
        ++showError.value();
    } else if (build == LDDrift::CompileBuildStatus::Idle) {
        ImGui::TextUnformatted("Idle");
    }
    if (showError.value() == 1) {
        for (const auto& [file, line, column, severity, message] : core->gui.CompilePTR->GetErrorLog()) {
            std::cout << "----------------------------" << std::endl;
            std::cout << "Error: " << message << std::endl;
            std::cout << "Line: " << line << " | ";
            std::cout << "Column: " << column << " | ";
            std::cout << "File: " << file << " | ";
            std::cout << "Severity: " << severity << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    }
#ifdef __linux__
    ImGui::Separator();
    if (ImGui::Button("Add Key Target")) {
        core->gui.GetWindowPTR(SET_KEY_TARGET_WINDOW_NAME)->Show = true;
    }
    ImGui::Separator();
    if (ImGui::Button("Reload Cmake File")) {
        std::string command =
            "cmake -S \"" + core->gui.ProjectWatchTower_PTR->GetProjectPath().string() +
            "\" -B \"" + core->gui.ProjectWatchTower_PTR->GetBuildFolderPath().string() +
            "\" 2>&1";

        core->gui.reloadCmakeFileThread = std::thread([command]()
        {
            FILE* pipe = popen(command.c_str(), "r");

            if (pipe == nullptr) {
                std::cout << "[CMake] Failed to start CMake.\n";
                return;
            }

            char buffer[4096 * 2];

            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                std::cout << buffer << std::flush;
            }

            pclose(pipe);
        });
    }
    if (core->gui.reloadCmakeFileThread.joinable()) {
        core->gui.reloadCmakeFileThread.join();
    }
    ImGui::Separator();
    static bool showExitMenu = false;
    if (ImGui::Button("Exit")) {
        if (core->gui.runGame) {
            showExitMenu = true;
        } else {
            core->engineRun = false;
        }
    }
    if (showExitMenu) {
        ImGui::TextUnformatted("Are you sure you want to exit the engine?");
        ImGui::TextUnformatted("Your game is currently running.");
        ImGui::TextUnformatted("Exiting the engine now may cause");
        ImGui::TextUnformatted("issues with your project.");
        if (ImGui::Button("YES")) {
            core->gui.runGame = false;
            core->engineRun = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("NO")) {
            showExitMenu = false;
        }
    }
#endif
}

const LDDrift::VecPos2D& LDDrift::Main_GraphicalWindow::GetPosition() const {
    return position;
}

const LDDrift::VecPos2D& LDDrift::Main_GraphicalWindow::GetSize() const {
    return size;
}

///////////// project watch tower /////////////

LDDrift::ProjectWatchTower_GraphicalWindow::ProjectWatchTower_GraphicalWindow() = default;

LDDrift::ProjectWatchTower_GraphicalWindow::~ProjectWatchTower_GraphicalWindow() = default;

void LDDrift::ProjectWatchTower_GraphicalWindow::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::ProjectWatchTower_GraphicalWindow::Initialize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();

    name = PROJECT_WATCH_TOWER_WINDOW_NAME;
    position = {0, windowSize.Y / 2};
    size = {350, windowSize.Y / 2};
    Show = true;
    canMoveWindow = false;
    canResizeWindow = false;
    std::memset(searchBuffer, '\0', sizeof(searchBuffer));
    SetTextPrintInWindow("");
}

void LDDrift::ProjectWatchTower_GraphicalWindow::Resize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();

    position = {0, windowSize.Y / 2};
    size = {350, windowSize.Y / 2};
}

void LDDrift::ProjectWatchTower_GraphicalWindow::Render() {
    ImGui::InputTextWithHint("##Create New File in User Project", "Enter File Name: ", createFileBuffer,
                             sizeof(createFileBuffer));
    if (ImGui::Button("Create New File")) {
        if (core->gui.ProjectWatchTower_PTR->FindFile(std::filesystem::path(createFileBuffer))) {
            std::cout << "Cannot create the file because a file with the same name already exists in the project." <<
                std::endl;
            return;
        }
        core->gui.ProjectWatchTower_PTR->CreateNewFile(std::filesystem::path(createFileBuffer));
        core->gui.ProjectWatchTower_PTR->SetPaths();
    }
    ImGui::Separator();
    ImGui::InputTextWithHint("##Open File Section", "Enter File Name: ", openFileBuffer, sizeof(openFileBuffer));
    if (ImGui::Button("Open")) {
        for (const std::filesystem::path& path : core->projectWatchTower.GetPaths()) {
            if (is_directory(path)) {
                continue;
            }
            if (path.filename().string() == std::string(openFileBuffer)) {
                std::ifstream inputFile(path, std::ios::binary);

                if (!inputFile.is_open()) {
                    std::cout << "Failed to open file: " << path.string() << std::endl;

                    break;
                }

                const std::string sourceCode(
                    (std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>()
                );
                core->gui.ImGuiEditorWindow.editorWindow.SetText(sourceCode);
                core->gui.ImGuiEditorWindow.name = path.string();
                core->gui.ImGuiEditorWindow.Show = true;

                break;
            }
        }
    }
    ImGui::Separator();
    ImGui::TextUnformatted("Project Information");
    ImGui::Separator();
    ImGui::Text("project name: %s", core->projectWatchTower.GetProjectName().c_str());
    ImGui::Text("project path: %s", core->projectWatchTower.GetProjectPath().c_str());
    ImGui::Separator();
    for (const std::filesystem::path& path : core->projectWatchTower.GetPaths()) {
        if (is_directory(path)) {
            continue;
        }
        ImGui::TextUnformatted(path.c_str());
    }
}

const LDDrift::VecPos2D& LDDrift::ProjectWatchTower_GraphicalWindow::GetPosition() const {
    return position;
}

const LDDrift::VecPos2D& LDDrift::ProjectWatchTower_GraphicalWindow::GetSize() const {
    return size;
}

///////////// console /////////////

LDDrift::Console_GraphicalWindow::Console_GraphicalWindow() = default;

LDDrift::Console_GraphicalWindow::~Console_GraphicalWindow() = default;

void LDDrift::Console_GraphicalWindow::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

void LDDrift::Console_GraphicalWindow::Initialize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();
    name = CONSOLE_WINDOW_NAME;
    position = {350, windowSize.Y - 180};
    size = {windowSize.X - 350, 180};
    Show = true;
    canMoveWindow = false;
    canResizeWindow = false;
    std::memset(searchBuffer, '\0', sizeof(searchBuffer));
    SetTextPrintInWindow("");
}

void LDDrift::Console_GraphicalWindow::Resize() {
    const LDDrift::VecPos2D windowSize = core->window.GetWindowSize();

    position = {350, windowSize.Y - 180};
}

void LDDrift::Console_GraphicalWindow::SetText(const std::string& text) {
    if (text != lastInputTextForSetTextFunction || std::ranges::find(texts, text) == texts.end()) {
        texts.clear();
        texts.push_back(text);
        lastInputTextForSetTextFunction = text;
    }
}

void LDDrift::Console_GraphicalWindow::Render() const {
    if (ImGui::Button("Clear")) {
        core->consoleBuffer.str("");
        core->consoleBuffer.clear();
    }
    for (const std::string& text : texts) {
        ImGui::TextUnformatted(text.c_str());
    }
}

const LDDrift::VecPos2D& LDDrift::Console_GraphicalWindow::GetPosition() const {
    return position;
}

const LDDrift::VecPos2D& LDDrift::Console_GraphicalWindow::GetSize() const {
    return size;
}
