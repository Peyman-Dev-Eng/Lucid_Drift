#ifndef LUCID_DRIFT_GUI_H
#define LUCID_DRIFT_GUI_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <Assertions.h>
#include <string>
#include <vector>
#include <VecPos.h>

namespace LDDrift
{
    class GUI
    {
    private:
        class Extract
        {
        public:
            static std::vector<std::string> ExtractTextFromString(const std::string& text);
        };
    private:
        struct DefaultWindowsData
        {
            std::string name;
            bool canMoveWindow;
            std::vector<std::string> textPrintInWindow;
            VecPos2D position;
            bool Show;
        };
        struct EditorWindowsData
        {
            std::string name;
            bool canMoveWindow;
            char codeBuffer[131072];
            bool Show;
        };

    private:
        EditorWindowsData editorWindow;
        std::vector<DefaultWindowsData> defaultWindows;

    public:
        explicit GUI(GLFWwindow* glfwWindow = nullptr);
        void CreateNewWindow(const std::string& name, bool canMoveWindow, const std::string& textPrintInWindow, const VecPos2D& position);
        void CreateNewEditor(const std::string& name, bool canMoveWindow);
        [[nodiscard]] const char* GetCodeBuffer() const;
        static void BeginRenderGUI();
        void EndRenderGUI();
        ~GUI();
    };
}
#endif
