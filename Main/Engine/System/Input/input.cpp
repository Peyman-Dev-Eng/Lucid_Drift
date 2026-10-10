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
    LDDrift::FileMouseInputEvent = open("/dev/input/by-id/usb-INSTANT_USB_GAMING_MOUSE-event-mouse",
                                        O_RDONLY | O_NONBLOCK);
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
    KeyBoardKeyName = {
        "Key_RESERVED",
        "Key_ESC",
        "Key_1",
        "Key_2",
        "Key_3",
        "Key_4",
        "Key_5",
        "Key_6",
        "Key_7",
        "Key_8",
        "Key_9",
        "Key_0",
        "Key_MINUS",
        "Key_EQUALS",
        "Key_BACKSPACE",
        "Key_TAB",
        "Key_Q",
        "Key_W",
        "Key_E",
        "Key_R",
        "Key_T",
        "Key_Y",
        "Key_U",
        "Key_I",
        "Key_O",
        "Key_P",
        "Key_LBRACKET",
        "Key_RBRACKET",
        "Key_ENTER",
        "Key_LCONTROL",
        "Key_A",
        "Key_S",
        "Key_D",
        "Key_F",
        "Key_G",
        "Key_H",
        "Key_J",
        "Key_K",
        "Key_L",
        "Key_SEMICOLON",
        "Key_APOSTROPHE",
        "Key_GRAVE",
        "Key_LSHIFT",
        "Key_BACKSLASH",
        "Key_Z",
        "Key_X",
        "Key_C",
        "Key_V",
        "Key_B",
        "Key_N",
        "Key_M",
        "Key_COMMA",
        "Key_DOT",
        "Key_SLASH",
        "Key_RSHIFT",
        "Key_KPASTERISK",
        "Key_LALT",
        "Key_SPACE",
        "Key_CAPSLOCK",
        "Key_F1",
        "Key_F2",
        "Key_F3",
        "Key_F4",
        "Key_F5",
        "Key_F6",
        "Key_F7",
        "Key_F8",
        "Key_F9",
        "Key_F10",
        "Key_NUMLOCK",
        "Key_SCROLLLOCK",
        "Key_KP7",
        "Key_KP8",
        "Key_KP9",
        "Key_KPMINUS",
        "Key_KP4",
        "Key_KP5",
        "Key_KP6",
        "Key_KPPLUS",
        "Key_KP1",
        "Key_KP2",
        "Key_KP3",
        "Key_KP0",
        "Key_KPDOT",
        "Key_RESERVED_84",
        "Key_ZENKAKUHANKAKU",
        "Key_102ND",
        "Key_F11",
        "Key_F12",
        "Key_RO",
        "Key_KATAKANA",
        "Key_HIRAGANA",
        "Key_HENKAN",
        "Key_KATAKANAHIRAGANA",
        "Key_MUHENKAN",
        "Key_KPJPCOMMA",
        "Key_KPENTER",
        "Key_RCONTROL",
        "Key_KPSLASH",
        "Key_SYSRQ",
        "Key_RALT",
        "Key_LINEFEED",
        "Key_HOME",
        "Key_UP",
        "Key_PAGEUP",
        "Key_LEFT",
        "Key_RIGHT",
        "Key_END",
        "Key_DOWN",
        "Key_PAGEDOWN",
        "Key_INSERT",
        "Key_DELETE",
        "Key_MACRO",
        "Key_MUTE",
        "Key_VOLUMEDOWN",
        "Key_VOLUMEUP",
        "Key_POWER",
        "Key_KPEQUAL",
        "Key_KPPLUSMINUS",
        "Key_PAUSE",
        "Key_SCALE",
        "Key_KPCOMMA",
        "Key_HANGEUL",
        "Key_HANJA",
        "Key_YEN",
        "Key_LMETA",
        "Key_RMETA",
        "Key_COMPOSE",
        "Key_STOP",
        "Key_AGAIN",
        "Key_PROPS",
        "Key_UNDO",
        "Key_FRONT",
        "Key_COPY",
        "Key_OPEN",
        "Key_PASTE",
        "Key_FIND",
        "Key_CUT",
        "Key_HELP",
        "Key_MENU",
        "Key_CALC",
        "Key_SETUP",
        "Key_SLEEP",
        "Key_WAKEUP",
        "Key_FILE",
        "Key_SENDFILE",
        "Key_DELETEFILE",
        "Key_XFER",
        "Key_PROG1",
        "Key_PROG2",
        "Key_WWW",
        "Key_MSDOS",
        "Key_COFFEE",
        "Key_ROTATE_DISPLAY",
        "Key_CYCLEWINDOWS",
        "Key_MAIL",
        "Key_BOOKMARKS",
        "Key_COMPUTER",
        "Key_BACK",
        "Key_FORWARD",
        "Key_CLOSECD",
        "Key_EJECTCD",
        "Key_EJECTCLOSECD",
        "Key_NEXTSONG",
        "Key_PLAYPAUSE",
        "Key_PREVIOUSSONG",
        "Key_STOPCD",
        "Key_RECORD",
        "Key_REWIND",
        "Key_PHONE",
        "Key_ISO",
        "Key_CONFIG",
        "Key_HOMEPAGE",
        "Key_REFRESH",
        "Key_EXIT",
        "Key_MOVE",
        "Key_EDIT",
        "Key_SCROLLUP",
        "Key_SCROLLDOWN",
        "Key_KPLEFTPAREN",
        "Key_KPRIGHTPAREN"
    };
#endif
}

void LDDrift::input::Keyboard::SetKeyTarget(const std::vector<Event::Keyboard::LinuxKeyboardKeyCode>& keys) {
    for (const auto& key : keys) {
        TargetKeys.push_back(key);
    }
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
    if (TargetKeys.empty()) {
        return;
    }
    input_event event{};
    while (true) {
        if (read(FileKeyboardInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (std::ranges::find(
                TargetKeys, static_cast<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode>(event.code)
            ) == TargetKeys.end()) {
                continue;
            }
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

bool LDDrift::input::Keyboard::IsKeyPressed(const Event::Keyboard::LinuxKeyboardKeyCode key) {
#ifdef __linux__
    GLB_assert(static_cast<LD_uint>(key) >= 0 && static_cast<LD_uint>(key) <= 125)
    return ((LinuxKeyboard[static_cast<LD_uint>(key)].Current == true) && (LinuxKeyboard[static_cast<LD_uint>(key)].
        Before == false));
#elifdef _WIN32
    GLB_assert(static_cast<LD_uint>(key) >= 0 && static_cast<LD_uint>(key) < 256)
    return WindowsKeyCodes[static_cast<LD_uint>(key)].Before == false && WindowsKeyCodes[static_cast<LD_uint>(key)].
        Current == true;
#endif
}

bool LDDrift::input::Keyboard::IsKeyHeld(const Event::Keyboard::LinuxKeyboardKeyCode key) {
#ifdef __linux__
    GLB_assert(static_cast<LD_uint>(key) >= 0 && static_cast<LD_uint>(key) <= 125);
    return ((LinuxKeyboard[static_cast<LD_uint>(key)].Current == true) && (LinuxKeyboard[static_cast<LD_uint>(key)].
        Before == true));
#elifdef _WIN32
    GLB_assert(static_cast<LD_uint>(key) >= 0 && static_cast<LD_uint>(key) < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == true;
#endif
}

bool LDDrift::input::Keyboard::IsKeyReleased(const Event::Keyboard::LinuxKeyboardKeyCode key) {
#ifdef __linux__
    GLB_assert(static_cast<LD_uint>(key) >= 0 && static_cast<LD_uint>(key) <= 125);
    return ((LinuxKeyboard[static_cast<LD_uint>(key)].Current == false) && (LinuxKeyboard[static_cast<LD_uint>(key)].
        Before == true));
#elifdef _WIN32
    GLB_assert(key >= 0 && key < 256)
    return WindowsKeyCodes[key].Before == true && WindowsKeyCodes[key].Current == false;
#endif
}

std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LDDrift::input::Keyboard::GetKeyPressed() {
#ifdef __linux__
    std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LKeyCodes; // linux key codes
    for (const auto& key : TargetKeys) {
        if (LinuxKeyboard[static_cast<LD_uint>(key)].Current == true && LinuxKeyboard[static_cast<LD_uint>(key)].Before
            == false) {
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

std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LDDrift::input::Keyboard::GetKeyHeld() {
#ifdef __linux__
    std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LKeyCodes; // linux key codes
    for (const auto& key : TargetKeys) {
        if (LinuxKeyboard[static_cast<LD_uint>(key)].Current == true && LinuxKeyboard[static_cast<LD_uint>(key)].Before
            == true) {
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

std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LDDrift::input::Keyboard::GetKeyReleased() {
#ifdef __linux__
    std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> LKeyCodes; // linux key codes
    for (const auto& key : TargetKeys) {
        if (LinuxKeyboard[static_cast<LD_uint>(key)].Current == false && LinuxKeyboard[static_cast<LD_uint>(key)].Before
            == true) {
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

void LDDrift::input::Mouse::GetMouseInputEvent() {
#ifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileMouseInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 1) {
                    const LD_uint MouseCode = event.code - 272;
                    LinuxMouse[MouseCode].Current = true;
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

LDDrift::VecPos2D LDDrift::input::Mouse::GetCursorPos(GLFWwindow* window) {
    double x = NAN, y = NAN;
    glfwGetCursorPos(window, &x, &y);
    return LDDrift::VecPos2D{static_cast<float>(x), static_cast<float>(y)};
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
#ifdef __linux__
    for (auto& mouseKey : LinuxMouse) {
        mouseKey.Before = mouseKey.Current;
        mouseKey.Current = mouseKey.Before;
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
