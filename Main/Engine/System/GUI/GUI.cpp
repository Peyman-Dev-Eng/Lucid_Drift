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
                                   const VecPos2D& size) {
    defaultWindows.push_back({
        .name = name, .canMoveWindow = canMoveWindow, .canResizeWindow = canResizeWindow,
        .textPrintInWindow = LDDrift::GUI::ExtractTextFromString(textPrintInWindow),
        .position = position, .size = size, .Show = true,
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
        for (const auto& path : ProjectWatchTower_PTR->GetPaths()) {
            if (LDDrift::ProjectWatchTower::Extract::GetLastFileName(path.string()) ==
                std::string(result.searchBuffer)) {
                editorWindow.Show = true;
                editorWindow.name = std::string(result.searchBuffer);
                std::ifstream ifile(path.string(), std::ios::binary | std::ios::ate);
                std::streamsize size = ifile.tellg();
                ifile.seekg(0, std::ios::beg);
                ifile.read(editorWindow.codeBuffer, size);
                break;
            }
        }
    }
}

void LDDrift::GUI::SetCorePTR(LDDrift::Core* corePTR) {
    NPV_assert(corePTR != nullptr)
    core = corePTR;
}

void LDDrift::GUI::EndRenderGUI() {
    GLB_assert(ProjectWatchTower_PTR != nullptr)
    for (DefaultWindowsData& window : defaultWindows) {
        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoCollapse;
        if (!window.canResizeWindow) {
            flags |= ImGuiWindowFlags_NoResize;
        }
        if (!window.canMoveWindow) {
            flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowSize(ImVec2(window.size.X, window.size.Y));
        ImGui::SetNextWindowPos(ImVec2(window.position.X, window.position.Y));
        ImGui::Begin(window.name.c_str(), nullptr, flags);
        this->ProjectWatchTowerWidowHandler(&window);
        if (window.name == CONSOLE_WINDOW_NAME) {
            if (ImGui::Button("Clear")) {
                core->consoleBuffer.str("");
                core->consoleBuffer.clear();
            }
        }
        LDDrift::GuiLogic::ProjectManagerHandling(&window);
        for (const std::string& text : window.textPrintInWindow) {
            ImGui::TextUnformatted(text.c_str());
        }
        ImGui::End();
    }
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
