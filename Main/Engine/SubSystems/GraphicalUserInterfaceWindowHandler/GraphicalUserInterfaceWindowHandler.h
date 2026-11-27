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
#ifndef LUCID_DRIFT_GRAPHICAL_USER_INTERFACE_WINDOW_HANDLER_H
#define LUCID_DRIFT_GRAPHICAL_USER_INTERFACE_WINDOW_HANDLER_H
#include <imgui.h>
#include <string>
#include <VecPos2D.h>
#include <vector>
#include <SubSystems/Logger/Logger.h>

namespace LDDrift
{
    class Core;

    struct DefaultWindowsData
    {
        std::string name;
        bool canMoveWindow;
        bool canResizeWindow;
        std::pmr::vector<std::string> textPrintInWindow;
        VecPos2D position;
        VecPos2D size;
        bool Show;
        char Buffer[256]{};

        void SetTextPrintInWindow(const std::string& text);
    };

    class Main_GraphicalWindow : private DefaultWindowsData
    {
    private:
        LDDrift::Core* core = nullptr;

    public:
        Main_GraphicalWindow();
        ~Main_GraphicalWindow();
        [[nodiscard]] const LDDrift::VecPos2D& GetPosition() const;
        [[nodiscard]] const LDDrift::VecPos2D& GetSize() const;
        void Initialize();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void Resize();
        void Render() const;
    };

    class ProjectWatchTower_GraphicalWindow final : private DefaultWindowsData
    {
    private:
        LDDrift::Core* core = nullptr;
        char FileBufferName[256]{};
        char openFileBuffer[256]{};

    public:
        ProjectWatchTower_GraphicalWindow();
        ~ProjectWatchTower_GraphicalWindow();
        [[nodiscard]] const LDDrift::VecPos2D& GetPosition() const;
        [[nodiscard]] const LDDrift::VecPos2D& GetSize() const;
        void Initialize();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void Resize();
        void Render();
    };

    class Console_GraphicalWindow final : private DefaultWindowsData
    {
    private:
        struct Text
        {
            std::string text;
            ImVec4 color;
        };
    private:
        LDDrift::Core* core = nullptr;
        std::pmr::vector<Text> texts;
        std::string lastInputTextForSetTextFunction;
    private:
        static std::pmr::vector<Text> ExtractTextFromString(const std::string& text);

    public:
        Console_GraphicalWindow();
        ~Console_GraphicalWindow();
        [[nodiscard]] const LDDrift::VecPos2D& GetPosition() const;
        [[nodiscard]] const LDDrift::VecPos2D& GetSize() const;
        void Initialize();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void SetText(const std::string& text);
        void Resize();
        void Render() const;
    };

    // create window title bar
} // LDDrift

#endif
