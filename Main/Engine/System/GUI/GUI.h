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
#include <optional>
#include <VecPos.h>
#include <imgui_internal.h>
#include <Compile.h>
#include <cstdio>
#include <iterator>
#include <GraphicalUserInterfaceWindowHandler.h>
#include "TextEditor.h"
#define PROJECT_WATCH_TOWER_WINDOW_NAME "Project Watch Tower"
#define PROJECT_MANAGER_WINDOW_NAME "Project Manager"
#define CONSOLE_WINDOW_NAME "Console"
#define MAIN_WINDOW_NAME "Main Window"
#define CIRCLE_CONFIGURE_WINDOW_NAME "Circle Configure Window"
#define POLYGON_CONFIGURE_WINDOW_NAME "Polygon Configure Window"
#define LINE_CONFIGURE_WINDOW_NAME "Line Configure Window"
#define SET_KEY_TARGET_WINDOW_NAME "Set Key Target"
#define EXIT_WARNING_WINDOW_NAME "Exit Warning Window"
#define CREATE_NEW_CIRCLE_ACTOR_WINDOW_NAME "Create New Circle Actor"
#define GAME_SETTING_WINDOW_NAME "Game Setting"

namespace LDDrift
{
    class Core;
}

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
    class GUI final
    {
    public:
        std::thread reloadCmakeFileThread;
    private: // editor window handing functions
        bool DrawCodeSuggestionPopup(bool& shouldOpen, const std::vector<std::string>& suggestions,
                                     std::string& selectedSuggestion, ImVec2 position = ImVec2(-1.0f, -1.0f)
        );

        struct PopupCompletionState
        {
            bool ShowPopup = false;
            bool WasOpen = false;

            bool IsOpenInBeforeFrame = false;

            int SelectedIndex = 0;

            ImVec2 Position = ImVec2(0.0f, 0.0f);

            std::string selectedSuggestion;
        };

        PopupCompletionState popupCompletionState;

        static void TransformString(std::string& text);
        static bool ValidChar(char c);
        void PopupCompletionLogic();

    private:
        LDDrift::Core* core = nullptr;

    public:
        static std::vector<std::string> ExtractTextFromString(const std::string& text);

    public:

        struct EditorWindowsData
        {
            char buffer[256];
            std::string name = NULL_STRING;
            TextEditor editorWindow;
            bool Show = false;
        };

    public:
        LDDrift::Console_GraphicalWindow consoleWindow;
        LDDrift::ProjectWatchTower_GraphicalWindow projectWatchTowerWindow;
        LDDrift::Main_GraphicalWindow mainWindow;
        EditorWindowsData ImGuiEditorWindow;
        std::vector<DefaultWindowsData> defaultWindows;
        LDDrift::ProjectWatchTower* ProjectWatchTower_PTR = nullptr;
        LDDrift::Compile* CompilePTR = nullptr;
        bool runGame = false;

    public:
        explicit GUI();
        void UpdateWindow(const std::string& windowName);
        void Initialize(GLFWwindow* glfwWindow);
        void SetProjectWatchTower_PTR(LDDrift::ProjectWatchTower* projectWatchTower);
        void SetCompilePTR(LDDrift::Compile* compilePTR);
        void CreateNewWindow(const std::string& name, bool canMoveWindow, bool canResizeWindow,
                             const std::string& textPrintInWindow,
                             const VecPos2D& position, const VecPos2D& size,
                             bool SHOW);
        void CreateNewEditor(const std::string& name, bool canShowWindow);
        [[nodiscard]] std::string GetCodeBuffer() const;
        void SetTextForWindow(const std::string& windowName, const std::string& text,
                              bool deletePreviousMessages = false);
        void RenameEditorWindow(const std::string& newWindowName);
        void SetCorePTR(LDDrift::Core* corePTR);
        void OpenWindow(const std::string& name);
        void SetShowEditorWindow(bool show);
        [[nodiscard]] DefaultWindowsData GetWindow(const std::string& nameWindow) const;
        DefaultWindowsData* GetWindowPTR(const std::string& nameWindow);
        static void BeginRenderGUI();
        void EndRenderGUI();
        static int CodeEditorCallback(ImGuiInputTextCallbackData* data);
        ~GUI();

    private:
        void GameSettingWindowHandler(DefaultWindowsData* window);
        void CircleConfigureWindowHandler(DefaultWindowsData* window);
        void PolygonConfigureWindowHandler(DefaultWindowsData* window) const;
        void LineConfigureWindowHandler(DefaultWindowsData* window) const;
        void SetKeyTargetWindowHandler(DefaultWindowsData* window) const;
        static bool SearchableCombo(char* buffer, const std::vector<std::string>& options);
    };
}
#endif
