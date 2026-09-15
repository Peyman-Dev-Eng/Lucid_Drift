#include "input.h"

void OpenFileKeyboardInputEvent() {
    FileKeyboardInputEvent = open("/dev/input/by-id/usb-SEMICO_USB_Keyboard-event-kbd", O_RDONLY | O_NONBLOCK);
    COF_assert(FileKeyboardInputEvent != -1)
}

void CloseFileKeyboardInputEvent() {
    close(FileKeyboardInputEvent);
}

void OpenFileMouseInputEvent() {
    FileMouseInputEvent = open("/dev/input/by-id/usb-INSTANT_USB_GAMING_MOUSE-event-mouse", O_RDONLY | O_NONBLOCK);
    COF_assert(FileMouseInputEvent != -1)
}

void CloseFileMouseInputEvent() {
    close(FileMouseInputEvent);
}

void input::Keyboard::Init() {
#ifdef _WIN32
    for (std::size_t KeyCode = 0; KeyCode < 256; ++KeyCode) {
        WindowsKeyCodes[KeyCode] = {false, false};
    }
#elifdef __linux__
    OpenFileKeyboardInputEvent();
    constexpr IsKeyPressedInFrame Default = {.Before = false, .Current = false};
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        LinuxKeyboard.push_back(Default);
    }
#endif
}

bool input::Keyboard::InputIsChar(const LD_lint& target) {
    if (target >= 65 && target <= 90) {
        return true;
    }
    if (target >= 97 && target <= 122) {
        return true;
    }
    return false;
}

void input::Keyboard::GetKeyInputEvent() {
#ifdef _WIN32
    for (std::size_t KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (GetAsyncKeyState(KeyCode) & 0x8000) {
            WindowsKeyCodes[KeyCode] = true;
        }
    }
#elifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileKeyboardInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 0) {
                    LinuxKeyboard[event.code].Current = false;
                } else if (event.value == 1) {
                    LinuxKeyboard[event.code].Current = true;
                }
            }
        } else {
            break;
        }
    }

#endif
}

bool input::Keyboard::IsKeyPressed(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125)
    return ((LinuxKeyboard[key].Current == true) && (LinuxKeyboard[key].Before == false));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == false && WindowsKeyCodes[key].Current == true;
#endif
}

bool input::Keyboard::IsKeyHeld(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125);
    return ((LinuxKeyboard[key].Current == true) && (LinuxKeyboard[key].Before == true));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == true;
#endif
}

bool input::Keyboard::IsKeyReleased(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125);
    return ((LinuxKeyboard[key].Current == false) && (LinuxKeyboard[key].Before == true));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == false;
#endif
}

std::vector<LD_lint> input::Keyboard::GetKeyPressed() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (LinuxKeyboard[KeyCode].Current == true && LinuxKeyboard[KeyCode].Before == false) {
            LKeyCodes.push_back(KeyCode);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (int KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (WindowsKeyCodes[KeyCode].Before == false && WindowsKeyCodes[KeyCode].Current == true) {
            WKeyCodes.push_back(KeyCode);
        }
    }
    return WKeyCodes;
#endif
}

std::vector<LD_lint> input::Keyboard::GetKeyHeld() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (LinuxKeyboard[KeyCode].Current == true && LinuxKeyboard[KeyCode].Before == true) {
            LKeyCodes.push_back(KeyCode);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (LD_lint KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (WindowsKeyCodes[KeyCode].Before == true && WindowsKeyCodes[KeyCode].Current == true) {
            WKeyCodes.push_back(KeyCode);
        }
    }
    return WKeyCodes;
#endif
}

std::vector<LD_lint> input::Keyboard::GetKeyReleased() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (LinuxKeyboard[KeyCode].Current == false && LinuxKeyboard[KeyCode].Before == true) {
            LKeyCodes.push_back(KeyCode);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (LD_lint KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (WindowsKeyCodes[KeyCode].Before == true && WindowsKeyCodes[KeyCode].Current == false) {
            WKeyCodes.push_back(KeyCode);
        }
    }
    return WKeyCodes;
#endif
}

void input::Keyboard::Update() {
#ifdef __linux__
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        LinuxKeyboard[KeyCode].Before = LinuxKeyboard[KeyCode].Current;
        LinuxKeyboard[KeyCode].Current = LinuxKeyboard[KeyCode].Before ? true : false;
    }
#elifdef _WIN32
    for (LD_uint KeyCode = 0; KeyCode < 256; ++KeyCode) {
        WindowsKeyCodes[KeyCode].Before = WindowsKeyCodes[KeyCode].Current;
        WindowsKeyCodes[KeyCode].Current = false;
    }
#endif
}

void input::Keyboard::Destroy() {
    CloseFileKeyboardInputEvent();
}

//////////////// mouse input event ////////////////

void input::Mouse::Init() {
#ifdef __linux__
    OpenFileMouseInputEvent();
    for (LD_uint MouseCode = 0; MouseCode < 5; ++MouseCode) {
        LinuxMouse.push_back({.Before = false, .Current = false});
    }
#elifdef _WIN32
    for (LD_uint counter = 0; counter < 256; ++counter) {
        WindowsKeyCodes[counter] = {false, false};
    }
#endif
}

void input::Mouse::GetMouseInputEvent() {
#ifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileMouseInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 1) {
                    LinuxMouse[event.code - 272].Current = true;
                } else if (event.value == 0) {
                    LinuxMouse[event.code - 272].Current = false;
                }
            }
        } else {
            break;
        }
    }
#elifdef _WIN32
    for (LD_lint KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (GetAsyncKeyState(KeyCode) & 0x8000) {
            WindowsKeyCodes[KeyCode].Current = true;
        }
    }
#endif
}

VecPos2D input::Mouse::GetCursorPos(GLFWwindow* window) {
    VecPos2D CursorPos;
    glfwGetCursorPos(window, &CursorPos.X, &CursorPos.Y);
    return CursorPos;
}

bool input::Mouse::IsLeftMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == false && LinuxMouse[LeftMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == false && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsLeftMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == true && LinuxMouse[LeftMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == true && WindowsKeyCodes[VK_RBUTTON].Current == true;
#endif
}

bool input::Mouse::IsLeftMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == true && LinuxMouse[LeftMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == true && WindowsKeyCodes[VK_RBUTTON].Current == false;
#endif
}

bool input::Mouse::IsRightMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == false && LinuxMouse[RightMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == false && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsRightMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == true && LinuxMouse[RightMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsRightMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == true && LinuxMouse[RightMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == false;
#endif
}

bool input::Mouse::IsMiddleMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == false && LinuxMouse[MiddleMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VM_MBUTTON].Before == false && WindowsKeyCodes[VM_MBUTTON].Current == true;
#endif
}

bool input::Mouse::IsMiddleMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == true && LinuxMouse[MiddleMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_MBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsMiddleMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == true && LinuxMouse[MiddleMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_MBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == false;
#endif
}

bool input::Mouse::IsXButton1Pressed() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == false && LinuxMouse[XButton1].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == false && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsXButton1Held() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == true && LinuxMouse[XButton1].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsXButton1Released() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == true && LinuxMouse[XButton1].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == false;
#endif
}

bool input::Mouse::IsXButton2Pressed() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == false && LinuxMouse[XButton2].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == false && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsXButton2Held() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == true && LinuxMouse[XButton2].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool input::Mouse::IsXButton2Released() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == true && LinuxMouse[XButton2].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == false;
#endif
}

void input::Mouse::Update() {
#ifdef __linux__
    for (LD_lint KeyCode = 0; KeyCode < 5; ++KeyCode) {
        LinuxMouse[KeyCode].Before = LinuxMouse[KeyCode].Current;
        LinuxMouse[KeyCode].Current = LinuxMouse[KeyCode].Before ? true : false;
    }
#elifdef _WIN32
    for (LD_lint KeyCode = 0; KeyCode < 256; ++KeyCode) {
        WindowsKeyCodes[KeyCode].Before = WindowsKeyCodes[KeyCode].Current;
        WindowsKeyCodes[KeyCode].Current = false;
    }
#endif
}

void input::Mouse::Destroy() {
    CloseFileMouseInputEvent();
}
