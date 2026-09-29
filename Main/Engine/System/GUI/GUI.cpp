#include "GUI.h"


LDDrift::GUI::GUI(GLFWwindow* glfwWindow) {
    //GLB_assert(glfwWindow != nullptr)
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init();
}

std::vector<std::string> LDDrift::GUI::Extract::ExtractTextFromString(const std::string& text) {
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
                                   const std::string& textPrintInWindow,
                                   const VecPos2D& position) {
    defaultWindows.push_back({
        .name = name, .canMoveWindow = canMoveWindow,
        .textPrintInWindow = LDDrift::GUI::Extract::ExtractTextFromString(textPrintInWindow),
        .position = position, .Show = true
    });
}

void LDDrift::GUI::BeginRenderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void LDDrift::GUI::EndRenderGUI() {
    for (const DefaultWindowsData& window : defaultWindows) {
        ImGui::Begin(window.name.c_str(), nullptr, window.canMoveWindow ? 0 : ImGuiWindowFlags_NoMove);
        for (const std::string& text : window.textPrintInWindow) {
            ImGui::TextUnformatted(text.c_str());
        }
        ImGui::End();
    }
    ImGui::Begin(editorWindow.name.c_str());

    if (ImGui::Button("Save")) {}

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
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const char* LDDrift::GUI::GetCodeBuffer() const {
    return editorWindow.codeBuffer;
}

void LDDrift::GUI::CreateNewEditor(const std::string& name, const bool canMoveWindow) {
    editorWindow.name = name;
    editorWindow.canMoveWindow = canMoveWindow;
    editorWindow.Show = true;
}

void LDDrift::GUI::SetTextForWindow(const std::string& windowName, const std::string& text,
                                    const bool deletePreviousMessages) {
    for (DefaultWindowsData& window : defaultWindows) {
        if (window.name == windowName) {
            if (deletePreviousMessages) {
                window.textPrintInWindow.clear();
            }
            for (const std::string& line : LDDrift::GUI::Extract::ExtractTextFromString(text)) {
                window.textPrintInWindow.push_back(line);
            }
            break;
        }
    }
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
