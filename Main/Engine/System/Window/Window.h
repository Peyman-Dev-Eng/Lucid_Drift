#ifndef LUCID_DRIFT_WINDOW_SYSTEM_H
#define LUCID_DRIFT_WINDOW_SYSTEM_H
#include <Assertions.h>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VecCol.h>
#include <VecPos.h>
#include <GUI.h>
#include <string>

namespace LDDrift
{
    class Transform;
    class Core;
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
    class Renderer;

    class Window
    {
    private:
        struct Settings
        {
            int viewPortWidth, viewPortHeight;
            int pos_x, pos_y;
            int width, height;
            bool CanResize;
            std::string title;
            int FramerateLimit;
            LDDrift::VecCol FillColorScreen;
            bool IsOpen;
        };

    private:
        LDDrift::Core* core = nullptr;
        LDDrift::Renderer* renderer;
        GLFWwindow* screen{nullptr};
        GLFWmonitor* monitor{nullptr};
        const GLFWvidmode* mode{nullptr};
        Settings settings;

    public:
        Window();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void SetRendererPTR(LDDrift::Renderer*);
        void CreateWindow();
        void CreateFullscreenWindow();
        void DestroyWindow() const;
        void SetFillScreenColor(const LDDrift::VecCol& color);
        [[nodiscard]] LDDrift::VecCol GetFillScreenColor() const;
        void LockWindow();
        void ClearBuffer() const;
        void SetTitle(const char* title);
        [[nodiscard]] const char* GetTitle() const;
        void SetSize(int width, int height);
        [[nodiscard]] LDDrift::VecPos2D GetWindowSize() const;
        [[nodiscard]] LDDrift::VecPos2D GetViewportSize() const;
        void SetPosition(int x, int y);
        [[nodiscard]] VecPos2D GetPosition() const;
        [[nodiscard]] LDDrift::VecPos2D GetCenterPosition() const;
        [[nodiscard]] int GetWidth() const;
        [[nodiscard]] int GetHeight() const;
        [[nodiscard]] GLFWwindow* GetWindow() const;
        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
        void Update();
        [[nodiscard]] bool ScreenIsOpen() const;
        ~Window();
    };
}

#endif
