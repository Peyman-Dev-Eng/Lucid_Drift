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
        struct WindowsData
        {
            std::string name;
            bool canMoveWindow;
            std::vector<std::string> textPrintInWindow;
            VecPos2D position;
        };

    private:
        std::vector<WindowsData> windows;

    public:
        explicit GUI(GLFWwindow* glfwWindow = nullptr);
        void CreateNewWindow(const std::string& name, bool canMoveWindow, const std::string& textPrintInWindow, const VecPos2D& position);
        static void BeginRenderGUI();
        void EndRenderGUI() const;
        ~GUI();
    };
}
#endif
