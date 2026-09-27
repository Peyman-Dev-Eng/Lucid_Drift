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
    windows.push_back({
        .name = name, .canMoveWindow = canMoveWindow,
        .textPrintInWindow = LDDrift::GUI::Extract::ExtractTextFromString(textPrintInWindow),
        .position = position
    });
}

void LDDrift::GUI::BeginRenderGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void LDDrift::GUI::EndRenderGUI() const {
    for (const WindowsData& window : windows) {
        ImGui::SetNextWindowPos(ImVec2(window.position.X, window.position.Y));
        ImGui::Begin(window.name.c_str(), nullptr, window.canMoveWindow ? 0 : ImGuiWindowFlags_NoMove);
        for (const std::string& text : window.textPrintInWindow) {
            ImGui::TextUnformatted(text.c_str());
        }
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

LDDrift::GUI::~GUI() = default;
