#ifndef LUCID_DRIFT_WINDOW_H
#define LUCID_DRIFT_WINDOW_H
#include <Assertions.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VecCol.h>

#include "VecPos.h"

namespace LDDrift
{
    class Window
    {
    private:
        struct Settings
        {
            int pos_x, pos_y;
            int width, height;
            bool CanResize;
            const char* title;
            int FramerateLimit;
            LDDrift::VecCol FillColorScreen;
            bool IsOpen;
        };

    private:
        GLFWwindow* screen{nullptr};
        Settings settings;
    private: // functions

    public:
        Window();
        void CreateWindow();
        void DestroyWindow() const;
        void SetFillScreenColor(const LDDrift::VecCol& color);
        [[nodiscard]] LDDrift::VecCol GetFillScreenColor() const;
        void ClearBuffer() const;
        void SetTitle(const char* title);
        [[nodiscard]] const char* GetTitle() const;
        void SetSize(int width, int height);
        [[nodiscard]] VecPos2D GetWindowSize() const;
        void SetPosition(int x, int y);
        [[nodiscard]] VecPos2D GetPosition() const;
        void Update();
        [[nodiscard]] bool ScreenIsOpen() const;
        ~Window();
    };
}

#endif
