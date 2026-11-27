/*
 * Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */

#ifndef LUCID_DRIFT_WINDOW_SYSTEM_H
#define LUCID_DRIFT_WINDOW_SYSTEM_H
#include <Assertions.h>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VecCol.h>
#include <VecPos2D.h>
#include <GUI.h>
#include <string>
#include <format>
#include <string_view>

namespace LDDrift
{
    class Transformer;
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
    class ShapeRender;

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
            LDDrift::Actors::Texture background;
            float moveBackground; // move
            int direction; // 0 = left | 1 = right | 10 = up | 11 = down
            bool IsOpen;
        };

    private:
        LDDrift::Core* core = nullptr;
        LDDrift::ShapeRender* s_renderer;
        GLFWwindow* screen{nullptr};
        GLFWmonitor* monitor{nullptr};
        const GLFWvidmode* mode{nullptr};
        Settings settings;

    public:
        Window();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void SetRendererPTR(LDDrift::ShapeRender*);
        void CreateWindow();
        void CreateFullscreenWindow();
        void DestroyWindow() const;
        void SetFillScreenColor(const LDDrift::VecCol& color);
        [[nodiscard]] LDDrift::VecCol GetFillScreenColor() const;
        void LockWindow(); // freeze
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
