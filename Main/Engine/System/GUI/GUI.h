#ifndef LUCID_DRIFT_GUI_H
#define LUCID_DRIFT_GUI_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"
#include <Assertions.h>
#include <string>
#include <vector>
#include <ProjectWatchTower.h>
#include <VecPos.h>

namespace LDDrift
{
    /**
     * @class GUI
     * @brief A class for creating and managing graphical user interfaces using ImGui.
     *
     * This class provides methods to create windows and an editor, set text in windows,
     * and manage the rendering of the GUI.
     *
     * @note This class uses ImGui for rendering the GUI. Ensure that ImGui is properly
     * initialized before creating an instance of this class.
     */
    class GUI
    {
    public:
        static std::vector<std::string> ExtractTextFromString(const std::string& text);

    public:
        struct DefaultWindowsData
        {
            std::string name;
            bool canMoveWindow;
            bool canResizeWindow;
            std::vector<std::string> textPrintInWindow;
            VecPos2D position;
            VecPos2D size;
            bool Show;
            char searchBuffer[256];
        };

        struct EditorWindowsData
        {
            std::string name;
            bool canMoveWindow;
            char codeBuffer[131072];
            bool Show;
        };

    public:
        EditorWindowsData editorWindow;
        std::vector<DefaultWindowsData> defaultWindows;
        LDDrift::ProjectWatchTower* ProjectWatchTower_PTR{};

    public:
        explicit GUI();
        void UpdateWindow(const std::string& windowName);
        void Initialize(GLFWwindow* glfwWindow);
        void SetProjectWatchTower_PTR(LDDrift::ProjectWatchTower* projectWatchTower);
        void CreateNewWindow(const std::string& name, bool canMoveWindow, bool canResizeWindow, const std::string& textPrintInWindow,
                             const VecPos2D& position, const VecPos2D& size);
        void CreateNewEditor(const std::string& name, bool canShowWindow);
        [[nodiscard]] const char* GetCodeBuffer() const;
        void SetTextForWindow(const std::string& windowName, const std::string& text,
                              bool deletePreviousMessages = false);
        void RenameEditorWindow(const std::string& newWindowName);
        void SetShowEditorWindow(bool show);
        [[nodiscard]] DefaultWindowsData GetWindow(const std::string& nameWindow) const;
        static void BeginRenderGUI();
        void EndRenderGUI();
        static int CodeEditorCallback(ImGuiInputTextCallbackData* data);
        ~GUI();
    };
}
#endif
