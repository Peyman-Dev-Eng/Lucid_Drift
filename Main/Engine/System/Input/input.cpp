#include "input.h"

void LDDrift::OpenFileKeyboardInputEvent() {
#ifdef __linux__
    LDDrift::FileKeyboardInputEvent = open("/dev/input/by-id/usb-SEMICO_USB_Keyboard-event-kbd", O_RDONLY | O_NONBLOCK);
    COF_assert(LDDrift::FileKeyboardInputEvent != -1)
#endif
}

void LDDrift::CloseFileKeyboardInputEvent() {
#ifdef __linux__
    close(LDDrift::FileKeyboardInputEvent);
#endif
}

void LDDrift::OpenFileMouseInputEvent() {
#ifdef __linux__
    LDDrift::FileMouseInputEvent = open("/dev/input/by-id/usb-INSTANT_USB_GAMING_MOUSE-event-mouse", O_RDONLY | O_NONBLOCK);
    COF_assert(LDDrift::FileMouseInputEvent != -1)
#endif
}

void LDDrift::CloseFileMouseInputEvent() {
#ifdef __linux__
    close(LDDrift::FileMouseInputEvent);
#endif
}

void LDDrift::input::Keyboard::Init() {
#ifdef _WIN32
    for (std::size_t KeyCode = 0; KeyCode < 256; ++KeyCode) {
        WindowsKeyCodes[KeyCode] = {false, false};
    }
#elifdef __linux__
    LDDrift::OpenFileKeyboardInputEvent();
    constexpr IsKeyPressedInFrame Default = {.Before = false, .Current = false};
    for (LD_uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        LinuxKeyboard.push_back(Default);
    }
#endif
}

void LDDrift::input::Keyboard::SetKeyTarget(std::vector<LD_uint>&& keys) {
    TargetKeys = std::move(keys);
}

bool LDDrift::input::Keyboard::InputIsChar(const LD_lint& target) {
    if (target >= 65 && target <= 90) {
        return true;
    }
    if (target >= 97 && target <= 122) {
        return true;
    }
    return false;
}

void LDDrift::input::Keyboard::GetKeyInputEvent() {
#ifdef _WIN32
    for (const LD_uint& key : TargetKeys) {
        WindowsKeyCodes[key].Current = (GetAsyncKeyState(key) & 0x8000) != 0;
        ToUpdateValues.push_back(key);
    }
#elifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileKeyboardInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 0) {
                    LinuxKeyboard[event.code].Current = false;
                    ToUpdateValues.push_back(event.code);
                } else if (event.value == 1) {
                    LinuxKeyboard[event.code].Current = true;
                    ToUpdateValues.push_back(event.code);
                }
            }
        } else {
            break;
        }
    }

#endif
}

bool LDDrift::input::Keyboard::IsKeyPressed(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125)
    return ((LinuxKeyboard[key].Current == true) && (LinuxKeyboard[key].Before == false));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == false && WindowsKeyCodes[key].Current == true;
#endif
}

bool LDDrift::input::Keyboard::IsKeyHeld(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125);
    return ((LinuxKeyboard[key].Current == true) && (LinuxKeyboard[key].Before == true));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == true;
#endif
}

bool LDDrift::input::Keyboard::IsKeyReleased(const LD_lint key) {
#ifdef __linux__
    GLB_assert(key >= 0 && key <= 125);
    return ((LinuxKeyboard[key].Current == false) && (LinuxKeyboard[key].Before == true));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == false;
#endif
}

std::vector<LD_lint> LDDrift::input::Keyboard::GetKeyPressed() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (const LD_uint& key : TargetKeys) {
        if (LinuxKeyboard[key].Current == true && LinuxKeyboard[key].Before == false) {
            LKeyCodes.push_back(key);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (const LD_uint& key : TargetKeys) {
        if (WindowsKeyCodes[key].Before == false && WindowsKeyCodes[key].Current == true) {
            WKeyCodes.push_back(key);
        }
    }
    return WKeyCodes;
#endif
}

std::vector<LD_lint> LDDrift::input::Keyboard::GetKeyHeld() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (const LD_uint& key : TargetKeys) {
        if (LinuxKeyboard[key].Current == true && LinuxKeyboard[key].Before == true) {
            LKeyCodes.push_back(key);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (const LD_uint& key : TargetKeys) {
        if (WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == true) {
            WKeyCodes.push_back(key);
        }
    }
    return WKeyCodes;
#endif
}

std::vector<LD_lint> LDDrift::input::Keyboard::GetKeyReleased() {
#ifdef __linux__
    std::vector<LD_lint> LKeyCodes; // linux key codes
    for (const LD_uint& key : TargetKeys) {
        if (LinuxKeyboard[key].Current == false && LinuxKeyboard[key].Before == true) {
            LKeyCodes.push_back(key);
        }
    }
    return LKeyCodes;
#elifdef _WIN32
    std::vector<LD_lint> WKeyCodes; // windows key codes
    for (const LD_uint& key : TargetKeys) {
        if (WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == false) {
            WKeyCodes.push_back(key);
        }
    }
    return WKeyCodes;
#endif
}

void LDDrift::input::Keyboard::Update() {
    if (ToUpdateValues.empty()) {
        return;
    }
#ifdef __linux__
    for (const LD_uint value : ToUpdateValues) {
        LinuxKeyboard[value].Before = LinuxKeyboard[value].Current;
        LinuxKeyboard[value].Current = LinuxKeyboard[value].Before ? true : false;
    }
#elifdef _WIN32
    for (const LD_uint& value : ToUpdateValues) {
        WindowsKeyCodes[value].Before = WindowsKeyCodes[value].Current;
    }
#endif
    ToUpdateValues.clear();
}

void LDDrift::input::Keyboard::Destroy() {
    CloseFileKeyboardInputEvent();
}

//////////////// mouse input event ////////////////

void LDDrift::input::Mouse::Init() {
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

void LDDrift::input::Mouse::SetKeyTarget(std::vector<LD_uint>&& keys) {
    TargetKeys = std::move(keys);
}

void LDDrift::input::Mouse::GetMouseInputEvent() {
#ifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileMouseInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 1) {
                    const LD_uint MouseCode = event.code - 272;
                    LinuxMouse[MouseCode].Current = true;
                    ToUpdateValues.push_back(MouseCode);
                } else if (event.value == 0) {
                    LinuxMouse[event.code - 272].Current = false;
                }
            }
        } else {
            break;
        }
    }
#elifdef _WIN32
    for (const LD_uint& key : TargetKeys) {
        WindowsKeyCodes[key].Current = (GetAsyncKeyState(key) & 0x8000) != 0;
        ToUpdateValues.push_back(key);
    }
#endif
}

LDDrift::VecPosition::VecPos2D LDDrift::input::Mouse::GetCursorPos(GLFWwindow* window) {
    VecPosition::VecPos2D CursorPos;
    glfwGetCursorPos(window, &CursorPos.X, &CursorPos.Y);
    return CursorPos;
}

bool LDDrift::input::Mouse::IsLeftMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == false && LinuxMouse[LeftMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == false && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsLeftMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == true && LinuxMouse[LeftMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsLeftMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint LeftMouseButton = 0;
    return LinuxMouse[LeftMouseButton].Before == true && LinuxMouse[LeftMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_LBUTTON].Before == true && WindowsKeyCodes[VK_LBUTTON].Current == false;
#endif
}

bool LDDrift::input::Mouse::IsRightMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == false && LinuxMouse[RightMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == false && WindowsKeyCodes[VK_RBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsRightMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == true && LinuxMouse[RightMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == true && WindowsKeyCodes[VK_RBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsRightMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint RightMouseButton = 1;
    return LinuxMouse[RightMouseButton].Before == true && LinuxMouse[RightMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_RBUTTON].Before == true && WindowsKeyCodes[VK_RBUTTON].Current == false;
#endif
}

bool LDDrift::input::Mouse::IsMiddleMouseButtonPressed() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == false && LinuxMouse[MiddleMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VM_MBUTTON].Before == false && WindowsKeyCodes[VM_MBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsMiddleMouseButtonHeld() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == true && LinuxMouse[MiddleMouseButton].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_MBUTTON].Before == true && WindowsKeyCodes[VM_MBUTTON].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsMiddleMouseButtonReleased() {
#ifdef __linux__
    constexpr LD_lint MiddleMouseButton = 2;
    return LinuxMouse[MiddleMouseButton].Before == true && LinuxMouse[MiddleMouseButton].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_MBUTTON].Before == true && WindowsKeyCodes[VM_MBUTTON].Current == false;
#endif
}

bool LDDrift::input::Mouse::IsXButton1Pressed() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == false && LinuxMouse[XButton1].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == false && WindowsKeyCodes[VK_XBUTTON1].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsXButton1Held() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == true && LinuxMouse[XButton1].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == true && WindowsKeyCodes[VK_XBUTTON1].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsXButton1Released() {
#ifdef __linux__
    constexpr LD_lint XButton1 = 3;
    return LinuxMouse[XButton1].Before == true && LinuxMouse[XButton1].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON1].Before == true && WindowsKeyCodes[VK_XBUTTON1].Current == false;
#endif
}

bool LDDrift::input::Mouse::IsXButton2Pressed() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == false && LinuxMouse[XButton2].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == false && WindowsKeyCodes[VK_XBUTTON2].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsXButton2Held() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == true && LinuxMouse[XButton2].Current == true;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == true && WindowsKeyCodes[VK_XBUTTON2].Current == true;
#endif
}

bool LDDrift::input::Mouse::IsXButton2Released() {
#ifdef __linux__
    constexpr LD_lint XButton2 = 4;
    return LinuxMouse[XButton2].Before == true && LinuxMouse[XButton2].Current == false;
#elifdef _WIN32
    return WindowsKeyCodes[VK_XBUTTON2].Before == true && WindowsKeyCodes[VK_XBUTTON2].Current == false;
#endif
}

void LDDrift::input::Mouse::Update() {
    if (ToUpdateValues.empty()) {
        return;
    }
#ifdef __linux__
    for (const LD_uint& value : ToUpdateValues) {
        LinuxMouse[value].Before = LinuxMouse[value].Current;
        LinuxMouse[value].Current = LinuxMouse[value].Before ? true : false;
        if (LinuxMouse[value].Current == false) {
            ToUpdateValues.erase(std::ranges::find(ToUpdateValues, value));
        }
    }
#elifdef _WIN32
    for (const LD_uint& value : ToUpdateValues) {
        WindowsKeyCodes[value].Before = WindowsKeyCodes[value].Current;
    }
#endif
}

void LDDrift::input::Mouse::Destroy() {
    CloseFileMouseInputEvent();
}
