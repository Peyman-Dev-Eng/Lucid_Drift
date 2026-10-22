#ifndef LUCID_DRIFT_GRAPHICAL_USERINTERFACE_WINDOW_HANDLER_H
#define LUCID_DRIFT_GRAPHICAL_USERINTERFACE_WINDOW_HANDLER_H
#include <string>
#include <VecPos.h>
#include <vector>

namespace LDDrift
{
    class Core;
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

    class ProjectWatchTower_GraphicalWindow : private DefaultWindowsData
    {
    private:
        LDDrift::Core* core = nullptr;
        char createFileBuffer[256]{};
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

    class Console_GraphicalWindow : private DefaultWindowsData
    {
    private:
        LDDrift::Core* core = nullptr;

    public:
        Console_GraphicalWindow();
        ~Console_GraphicalWindow();
        [[nodiscard]] const LDDrift::VecPos2D& GetPosition() const;
        [[nodiscard]] const LDDrift::VecPos2D& GetSize() const;
        void Initialize();
        void SetCorePTR(LDDrift::Core* core_ptr);
        void Resize();
        void Render() const;
    };
} // LDDrift

#endif
