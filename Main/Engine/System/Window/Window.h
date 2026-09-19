#ifndef LUCID_DRIFT_WINDOW_H
#define LUCID_DRIFT_WINDOW_H
#include <Assertions.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VecCol.h>
#include <VecPos.h>
#include <string>

namespace LDDrift
{
    /**
     * Window class represents a graphical window in the application.
     *
     * @class Window
     *
     * @class LDDrift::Window
     * @brief Represents a graphical window.
     *
     * The Window class provides a high-level interface for creating and managing
     * a graphical window. It encapsulates various properties such as position,
     * size, title, and color, as well as methods for window management and rendering.
     *
     * @note The class uses GLFW and GLAD for window and OpenGL context management.
     * Ensure that these libraries are properly linked and initialized before using
     * this class.
     *
     * @see LDDrift::VecCol
     */
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
        [[nodiscard]] LDDrift::VecPos2D GetCenterPosition() const;
        void Update();
        [[nodiscard]] bool ScreenIsOpen() const;
        ~Window();
    };
}

#endif
