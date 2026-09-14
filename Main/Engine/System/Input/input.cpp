#include "input.h"

void OpenFileInputEvent() {
    FileInputEvent = open("/dev/input/by-id/usb-SEMICO_USB_Keyboard-event-kbd", O_RDONLY | O_NONBLOCK);
    COF_assert(FileInputEvent != -1)
}

void CloseFileInputEvent() {
    close(FileInputEvent);
}

void input::Keyboard::init() {
#ifdef _WIN32
    for (std::size_t KeyCode = 0; KeyCode < 256; ++KeyCode) {
        WindowsKeyCodes[KeyCode] = {false, false};
    }
#elifdef __linux__
    OpenFileInputEvent();
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
        if (read(FileInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
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
