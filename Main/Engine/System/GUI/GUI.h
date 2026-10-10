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
#include <Compile.h>
#define PROJECT_WATCH_TOWER_WINDOW_NAME "Project Watch Tower"
#define PROJECT_WATCH_TOWER_X_SIZE 350
#define PROJECT_WATCH_TOWER_Y_SIZE 540
#define PROJECT_MANAGER_WINDOW_NAME "Project Manager"
#define PROJECT_MANAGER_X_SIZE 350
#define PROJECT_MANAGER_Y_SIZE 540
#define CONSOLE_WINDOW_NAME "Console"
#define CONSOLE_X_SIZE 1570
#define CONSOLE_Y_SIZE 180
#define MAIN_WINDOW_NAME "Main Window"
#define MAIN_WINDOW_X_SIZE 350
#define MAIN_WINDOW_Y_SIZE 600
#define CIRCLE_CONFIGURE_WINDOW_NAME "Circle Configure Window"
#define POLYGON_CONFIGURE_WINDOW_NAME "Polygon Configure Window"
#define LINE_CONFIGURE_WINDOW_NAME "Line Configure Window"
#define SET_KEY_TARGET_WINDOW_NAME "Set Key Target"

namespace LDDrift
{
    class Core;
    class GuiLogic;
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
    class GUI
    {
    private:
        LDDrift::Core* core = nullptr;

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
        [[nodiscard]] const char* GetCodeBuffer() const;
        void SetTextForWindow(const std::string& windowName, const std::string& text,
                              bool deletePreviousMessages = false);
        void RenameEditorWindow(const std::string& newWindowName);
        void SetCorePTR(LDDrift::Core* corePTR);
        void SetShowEditorWindow(bool show);
        [[nodiscard]] DefaultWindowsData GetWindow(const std::string& nameWindow) const;
        DefaultWindowsData* GetWindowPTR(const std::string& nameWindow);
        static void BeginRenderGUI();
        void EndRenderGUI();
        static int CodeEditorCallback(ImGuiInputTextCallbackData* data);
        ~GUI();

    private:
        void ProjectWatchTowerWidowHandler(DefaultWindowsData* window);
        void MainWindowHandler(const DefaultWindowsData* window);
        static void CircleConfigureWindowHandler(DefaultWindowsData* window);
        static void PolygonConfigureWindowHandler(DefaultWindowsData* window);
        static void LineConfigureWindowHandler(DefaultWindowsData* window);
        void SetKeyTargetWindowHandler(DefaultWindowsData* window);
        bool SearchableCombo( const char* label, char* buffer, size_t bufferSize, const std::vector<std::string>& options);
    };
}
#endif
