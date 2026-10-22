#ifndef LUCID_DRIFT_GRAPHICAL_USERINTERFACE_WINDOW_HANDLER_H
#define LUCID_DRIFT_GRAPHICAL_USERINTERFACE_WINDOW_HANDLER_H
#include <string>
#include <VecPos.h>
#include <vector>

namespace LDDrift
{
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

    class GraphicalUserInterfaceWindowHandler : private DefaultWindowsData
    {
    private:
        std::string windowName;

    public:
        GraphicalUserInterfaceWindowHandler();
    };
} // LDDrift

#endif
