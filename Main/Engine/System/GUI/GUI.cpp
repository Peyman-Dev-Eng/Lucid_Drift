#include "GUI.h"
#include <GuiLogic.h>
#include "System/Core/Core.h"


LDDrift::GUI::GUI() = default;

void LDDrift::GUI::Initialize(GLFWwindow* glfwWindow) {
    GLB_assert(glfwWindow != nullptr)
    ProjectWatchTower_PTR = nullptr;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init();
    this->CreateNewWindow(PROJECT_WATCH_TOWER_WINDOW_NAME, false, true,
                          "", {0, 720}, {350, 360}, true);
    this->CreateNewWindow(PROJECT_MANAGER_WINDOW_NAME, false, true,
                          "", {0, 600}, {350, 120}, true);
    this->CreateNewWindow(CONSOLE_WINDOW_NAME, false, true,
                          "", {350, 900}, {1570, 180}, true);
    this->CreateNewWindow(MAIN_WINDOW_NAME, false, true,
                          "", {0, 0}, {350, 600}, true);
    this->CreateNewWindow(CIRCLE_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(POLYGON_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(LINE_CONFIGURE_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
    this->CreateNewWindow(SET_KEY_TARGET_WINDOW_NAME, true, true,
                          "", {10, 10}, {100, 100}, false);
}

std::vector<std::string> LDDrift::GUI::ExtractTextFromString(const std::string& text) {
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
    return result;
}

void LDDrift::GUI::CreateNewWindow(const std::string& name,
                                   const bool canMoveWindow,
                                   const bool canResizeWindow,
                                   const std::string& textPrintInWindow,
                                   const VecPos2D& position,
                                   const VecPos2D& size,
                                   const bool SHOW) {
    defaultWindows.push_back({
        .name = name, .canMoveWindow = canMoveWindow, .canResizeWindow = canResizeWindow,
        .textPrintInWindow = LDDrift::GUI::ExtractTextFromString(textPrintInWindow),
        .position = position, .size = size, .Show = SHOW,
    });
}

void LDDrift::GUI::BeginRenderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

LDDrift::GUI::DefaultWindowsData LDDrift::GUI::GetWindow(const std::string& nameWindow) const {
    for (const auto& window : defaultWindows) {
        if (window.name == nameWindow) {
            return window;
        }
    }
    return {
        .name = NULL_STR_VALUE, .canMoveWindow = false, .canResizeWindow = false, .textPrintInWindow = {},
        .position = {0, 0}, .size = {0, 0}
    };
}

void LDDrift::GUI::ProjectWatchTowerWidowHandler(DefaultWindowsData* window) {
    if (window->name != PROJECT_WATCH_TOWER_WINDOW_NAME) {
        return;
    }
    if (DefaultWindowsData result = LDDrift::GuiLogic::PressEnterInSearchBarInProjectWatchTower(window);
        result.name != NULL_STR_VALUE) {
        if (!ProjectWatchTower_PTR->FindFile(std::filesystem::path(result.searchBuffer))) {
            std::cout << "Not Found File! File: " << result.searchBuffer << std::endl;
            return;
        }
        for (const std::vector<std::filesystem::path>& paths = ProjectWatchTower_PTR->GetPaths();
             const auto& path : paths) {
            std::cout << path.string() << std::endl;
            if (LDDrift::ProjectWatchTower::Extract::GetLastFileName(path.string()) ==
                std::string(result.searchBuffer)) {
                if (is_directory(path)) {
                    std::cout <<
                        "Invalid input. The specified path is a folder. Please provide a file path where the code can be written."
                        << std::endl;
                    return;
                }
                editorWindow.Show = true;
                editorWindow.name = path.string();
                std::ifstream ifile(path.string(), std::ios::binary | std::ios::ate | std::ios::in);
                std::streamsize size = ifile.tellg();
                std::memset(editorWindow.codeBuffer, '\0', sizeof(editorWindow.codeBuffer));
                ifile.seekg(0, std::ios::beg);
                ifile.read(editorWindow.codeBuffer, size);
                break;
            }
        }
    }
    ImGui::Text("Project Information");

    ImGui::Separator();

    ImGui::Text((static_cast<std::string>("Project name: ") + ProjectWatchTower_PTR->GetProjectName()).c_str());

    ImGui::Text(
        (static_cast<std::string>("Project path: ") + ProjectWatchTower_PTR->GetProjectPath().string()).c_str());

    ImGui::Separator();

    for (const auto& path : ProjectWatchTower_PTR->GetPaths()) {
        ImGui::TextUnformatted(path.string().c_str());
    }
}

void LDDrift::GUI::SetCorePTR(LDDrift::Core* corePTR) {
    NPV_assert(corePTR != nullptr)
    core = corePTR;
}

LDDrift::GUI::DefaultWindowsData* LDDrift::GUI::GetWindowPTR(const std::string& nameWindow) {
    const std::size_t windowNumber = defaultWindows.size();
    for (std::size_t windowIndex = 0; windowIndex < windowNumber; ++windowIndex) {
        if (defaultWindows[windowIndex].name == nameWindow) {
            return &defaultWindows[windowIndex];
        }
    }
    return nullptr;
}

void LDDrift::GUI::MainWindowHandler(DefaultWindowsData* window) {
    if (window->name != MAIN_WINDOW_NAME) {
        return;
    }
    ImGui::Text("Create New");
    ImGui::Separator();
    if (ImGui::Button("Circle")) {
        DefaultWindowsData* circleConfigureWindow = GetWindowPTR(CIRCLE_CONFIGURE_WINDOW_NAME);
        NPV_assert(circleConfigureWindow != nullptr);
        circleConfigureWindow->Show = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Polygon")) {
        DefaultWindowsData* polygonConfigureWindow = GetWindowPTR(POLYGON_CONFIGURE_WINDOW_NAME);
        NPV_assert(polygonConfigureWindow != nullptr);
        polygonConfigureWindow->Show = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Line")) {
        DefaultWindowsData* lineConfigureWindow = GetWindowPTR(LINE_CONFIGURE_WINDOW_NAME);
        NPV_assert(lineConfigureWindow != nullptr);
        lineConfigureWindow->Show = true;
    }
    ImGui::Separator();
    if (ImGui::Button("Compile")) {
        CompilePTR->BuildProject();
    }
    ImGui::SameLine();
    LDDrift::CompileBuildStatus build = CompilePTR->GetStatus();
    if (ImGui::Button("Run")) {
        if (build == LDDrift::CompileBuildStatus::Succeeded) {
            runGame = true;
            LDDrift::EngineAPI::AfterCompileProject();
        }
    }
    ImGui::TextUnformatted("Build Status: ");
    ImGui::SameLine();
    if (build == LDDrift::CompileBuildStatus::Building) {
        ImGui::TextUnformatted("Compiling...");
    } else if (build == LDDrift::CompileBuildStatus::Succeeded) {
        ImGui::TextUnformatted("compiled");
    } else if (build == LDDrift::CompileBuildStatus::Failed) {
        ImGui::TextUnformatted("failed");
    } else if (build == LDDrift::CompileBuildStatus::Idle) {
        ImGui::TextUnformatted("idle");
    }
#ifdef __linux__
    ImGui::Separator();
    if (ImGui::Button("Add Key Target")) {
        GetWindowPTR(SET_KEY_TARGET_WINDOW_NAME)->Show = true;
    }
#endif
}

void LDDrift::GUI::SetCompilePTR(LDDrift::Compile* compilePTR) {
    CompilePTR = compilePTR;
}

void LDDrift::GUI::CircleConfigureWindowHandler(DefaultWindowsData* window) {
    if (window->name != CIRCLE_CONFIGURE_WINDOW_NAME) {
        return;
    }
    if (ImGui::Button("Close")) {
        window->Show = false;
    }
}

void LDDrift::GUI::LineConfigureWindowHandler(DefaultWindowsData* window) {
    if (window->name != LINE_CONFIGURE_WINDOW_NAME) {
        return;
    }
    if (ImGui::Button("Close")) {
        window->Show = false;
    }
}

void LDDrift::GUI::PolygonConfigureWindowHandler(DefaultWindowsData* window) {
    if (window->name != POLYGON_CONFIGURE_WINDOW_NAME) {
        return;
    }
    if (ImGui::Button("Close")) {
        window->Show = false;
    }
}

bool LDDrift::GUI::SearchableCombo(const char* label, char* buffer, size_t bufferSize,
                                   const std::vector<std::string>& options) {
    bool selected = false;
    ImGui::SetNextItemWidth(250.0f);
    ImGui::InputTextWithHint(label, "Search...", buffer, bufferSize);
    const std::string searchText = buffer;
    if (ImGui::IsItemActivated() || ImGui::IsItemActive()) { ImGui::OpenPopup(label); }
    if (ImGui::BeginPopup(label)) {
        for (const std::string& option : options) {
            if (!searchText.empty()) { if (option.find(searchText) == std::string::npos) continue; }
            if (ImGui::Selectable(option.c_str())) {
                const size_t length = std::min(option.size(), bufferSize - 1);
                std::copy_n(option.data(), length, buffer);
                buffer[length] = '\0';
                selected = true;
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }
    return selected;
}

void LDDrift::GUI::SetKeyTargetWindowHandler(DefaultWindowsData* window) {
    if (window->name != SET_KEY_TARGET_WINDOW_NAME) {
        return;
    }
    char search[256];
    if (this->SearchableCombo(" ", window->searchBuffer, sizeof(window->searchBuffer), LDDrift::KeyBoardKeyName))
        for (int i = 0; i < 256; ++i) {
             search[i] = window->searchBuffer[i];
        }
    ImGui::Separator();
    if (ImGui::Button("Set")) {
        window->Show = false;
    }
}

void LDDrift::GUI::EndRenderGUI() {
    GLB_assert(ProjectWatchTower_PTR != nullptr)
    for (DefaultWindowsData& window : defaultWindows) {
        if (!window.Show) {
            continue;
        }
        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoCollapse;
        if (!window.canResizeWindow) {
            flags |= ImGuiWindowFlags_NoResize;
        }
        if (!window.canMoveWindow) {
            flags |= ImGuiWindowFlags_NoMove;
        }
        if ((window.name != CIRCLE_CONFIGURE_WINDOW_NAME) && (window.name != POLYGON_CONFIGURE_WINDOW_NAME) && (window.
            name != LINE_CONFIGURE_WINDOW_NAME) && (window.name != SET_KEY_TARGET_WINDOW_NAME)) {
            ImGui::SetNextWindowSize(ImVec2(window.size.X, window.size.Y));
            ImGui::SetNextWindowPos(ImVec2(window.position.X, window.position.Y));
        }
        ImGui::Begin(window.name.c_str(), nullptr, flags);
        // مدیریت صفحه اصلی بازی
        MainWindowHandler(&window);
        // مدیریت صفحه ساخت دایره
        CircleConfigureWindowHandler(&window);
        // مدیریت صفحه ساخت خط
        LineConfigureWindowHandler(&window);
        // مدیریت صفحه ساخت چند ضلعی
        PolygonConfigureWindowHandler(&window);
        // مدیریت صفحه برج دیده بانی پروژه موتور بازی
        this->ProjectWatchTowerWidowHandler(&window);

        this->SetKeyTargetWindowHandler(&window);
        if (window.name == PROJECT_WATCH_TOWER_WINDOW_NAME) {
            ImGui::End();
            continue;
        }
        // مدیریت صفحه console موتور بازی
        if (window.name == CONSOLE_WINDOW_NAME) {
            if (ImGui::Button("Clear")) {
                core->consoleBuffer.str("");
                core->consoleBuffer.clear();
            }
        }
        // مدیریت صفحه مدیریت پروژه موتور بازی
        LDDrift::GuiLogic::ProjectManagerHandling(&window);
        if (!window.textPrintInWindow.empty())
            for (const std::string& text : window.textPrintInWindow) {
                ImGui::TextUnformatted(text.c_str());
            }
        ImGui::End();
    }
    // میدیریت ادیتور موتور بازی
    if (editorWindow.Show) {
        ImGui::Begin(editorWindow.name.c_str());

        if (ImGui::Button("Save")) {
            NPV_assert(ProjectWatchTower_PTR != nullptr)
            ProjectWatchTower_PTR->WriteCodeToFile(editorWindow.name, editorWindow.codeBuffer);
        }

        ImGui::SameLine();

        if (ImGui::Button("Exit")) {
            editorWindow.Show = false;
        }

        ImGui::Separator();

        ImGui::InputTextMultiline(
            "##Code",
            editorWindow.codeBuffer,
            sizeof(editorWindow.codeBuffer),
            ImVec2(-1, -1),
            ImGuiInputTextFlags_CallbackCompletion,
            CodeEditorCallback
        );

        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LDDrift::GUI::UpdateWindow(const std::string& windowName) {
    for (auto& window : defaultWindows) {
        if (window.name == windowName) {
            window.textPrintInWindow.clear();
            break;
        }
    }
}

const char* LDDrift::GUI::GetCodeBuffer() const {
    return editorWindow.codeBuffer;
}

void LDDrift::GUI::SetProjectWatchTower_PTR(LDDrift::ProjectWatchTower* projectWatchTower) {
    ProjectWatchTower_PTR = projectWatchTower;
}

void LDDrift::GUI::CreateNewEditor(const std::string& name, const bool canShowWindow) {
    editorWindow.name = name;
    editorWindow.canMoveWindow = true;
    editorWindow.Show = canShowWindow;
}

void LDDrift::GUI::SetTextForWindow(const std::string& windowName, const std::string& text,
                                    const bool deletePreviousMessages) {
    for (DefaultWindowsData& window : defaultWindows) {
        if (window.name == windowName) {
            if (deletePreviousMessages) {
                window.textPrintInWindow.clear();
            }
            for (const std::string& line : LDDrift::GUI::ExtractTextFromString(text)) {
                window.textPrintInWindow.push_back(line);
            }
            break;
        }
    }
}

void LDDrift::GUI::RenameEditorWindow(const std::string& newWindowName) {
    editorWindow.name = newWindowName;
}

void LDDrift::GUI::SetShowEditorWindow(const bool show) {
    editorWindow.Show = show;
}

int LDDrift::GUI::CodeEditorCallback(ImGuiInputTextCallbackData* data) {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion &&
        data->EventKey == ImGuiKey_Tab) {
        constexpr const char* Indentation = "    ";

        if (data->HasSelection()) {
            const int SelectionStart = data->SelectionStart;
            const int SelectionSize =
                data->SelectionEnd - data->SelectionStart;

            data->DeleteChars(SelectionStart, SelectionSize);
            data->InsertChars(SelectionStart, Indentation);
        } else {
            data->InsertChars(data->CursorPos, Indentation);
        }
    }

    return 0;
}

LDDrift::GUI::~GUI() = default;
