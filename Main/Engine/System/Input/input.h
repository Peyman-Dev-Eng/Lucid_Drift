#ifndef LUCID_DRIFT_INPUT_H
#define LUCID_DRIFT_INPUT_H

#define NOT_AVAILABLE_OS 0
#include <unordered_map>
#include <Assertions.h>
#include <array>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VecPos.h>

using LD_uint = unsigned int;
using LD_lint = long int;
using LD_ulint = unsigned long int;

struct IsKeyPressedInFrame
{
    bool Before;
    bool Current;
};
#ifdef _WIN32
#include <windows.h>
std::array<IsKeyPressedInFrame, 256> WindowsKeyCodes;
void GetWindowsInputEvent() {
    for (std::size_t KeyCode = 0; KeyCode < 256; ++KeyCode) {
        if (GetAsyncKeyState(KeyCode) & 0x8000) {
            WindowsKeyCodes[KeyCode] = true;
        }
    }
}

#elifdef __linux__
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <vector>
#define NO_EVENT_IS_AVAILABLE_TO_READ (-1)


namespace Event::Mouse
{
    enum LinuxMouseKeyCode : LD_lint
    {
        LeftButton = static_cast<LD_lint>(272),
        RightButton = static_cast<LD_lint>(273),
        MiddleButton = static_cast<LD_lint>(274),
        XButton1 = static_cast<LD_lint>(275),
        XButton2 = static_cast<LD_lint>(276)
    };
}

namespace Event::Keyboard
{
    enum LinuxKeyboardKeyCode : LD_lint
    {
        Key_RESERVED,
        Key_ESC,
        Key_1,
        Key_2,
        Key_3,
        Key_4,
        Key_5,
        Key_6,
        Key_7,
        Key_8,
        Key_9,
        Key_0,
        Key_MINUS,
        Key_EQUALS,
        Key_BACKSPACE,
        Key_TAB,
        Key_Q,
        Key_W,
        Key_E,
        Key_R,
        Key_T,
        Key_Y,
        Key_U,
        Key_I,
        Key_O,
        Key_P,
        Key_LBRACKET,
        Key_RBRACKET,
        Key_ENTER,
        Key_LCONTROL,
        Key_A,
        Key_S,
        Key_D,
        Key_F,
        Key_G,
        Key_H,
        Key_J,
        Key_K,
        Key_L,
        Key_SEMICOLON,
        Key_APOSTROPHE,
        Key_GRAVE,
        Key_LSHIFT,
        Key_BACKSLASH,
        Key_Z,
        Key_X,
        Key_C,
        Key_V,
        Key_B,
        Key_N,
        Key_M,
        Key_COMMA,
        Key_DOT,
        Key_SLASH,
        Key_RSHIFT,
        Key_KPASTERISK,
        Key_LALT,
        Key_SPACE,
        Key_CAPSLOCK,
        Key_F1,
        Key_F2,
        Key_F3,
        Key_F4,
        Key_F5,
        Key_F6,
        Key_F7,
        Key_F8,
        Key_F9,
        Key_F10,
        Key_NUMLOCK,
        Key_SCROLLLOCK,
        Key_KP7,
        Key_KP8,
        Key_KP9,
        Key_KPMINUS,
        Key_KP4,
        Key_KP5,
        Key_KP6,
        Key_KPPLUS,
        Key_KP1,
        Key_KP2,
        Key_KP3,
        Key_KP0,
        Key_KPDOT,
        Key_ZENKAKUHANKAKU,
        Key_102ND,
        Key_F11,
        Key_F12,
        Key_RO,
        Key_KATAKANA,
        Key_HIRAGANA,
        Key_HENKAN,
        Key_KATAKANAHIRAGANA,
        Key_MUHENKAN,
        Key_KPJPCOMMA,
        Key_KPENTER,
        Key_RCONTROL,
        Key_KPSLASH,
        Key_SYSRQ,
        Key_RALT,
        Key_LINEFEED,
        Key_HOME,
        Key_UP,
        Key_PAGEUP,
        Key_LEFT,
        Key_RIGHT,
        Key_END,
        Key_DOWN,
        Key_PAGEDOWN,
        Key_INSERT,
        Key_DELETE,
        Key_MACRO,
        Key_MUTE,
        Key_VOLUMEDOWN,
        Key_VOLUMEUP,
        Key_POWER,
        Key_KPEQUAL,
        Key_KPPLUSMINUS,
        Key_PAUSE,
        Key_SCALE,
        Key_KPCOMMA,
        Key_HANGEUL,
        Key_HANJA,
        Key_LMETA,
        Key_RMETA,
    };
}

inline int FileKeyboardInputEvent; // this variable just can use on linux os
inline int FileMouseInputEvent;

// keyboard
void OpenFileKeyboardInputEvent(); // open file input event of linux and save result this up variable
inline void CloseFileKeyboardInputEvent(); // close file input event of linux

// mouse
void OpenFileMouseInputEvent();
inline void CloseFileMouseInputEvent();


// Keyboard
inline std::vector<IsKeyPressedInFrame> LinuxKeyboard;

// Mouse
inline std::vector<IsKeyPressedInFrame> LinuxMouse;


#endif


namespace input
{
    class Keyboard
    {
    private:
        static bool InputIsChar(const LD_lint& target);

    public:
        static void Init();
        static void GetKeyInputEvent();
        static bool IsKeyPressed(LD_lint key);
        static bool IsKeyHeld(LD_lint key);
        static bool IsKeyReleased(LD_lint key);
        static std::vector<LD_lint> GetKeyPressed();
        static std::vector<LD_lint> GetKeyHeld();
        static std::vector<LD_lint> GetKeyReleased();
        static void Update();
        static void Destroy();
    };

    class Mouse
    {
    public:
        static void Init();
        static void GetMouseInputEvent();
        static VecPos2D GetCursorPos(GLFWwindow* window);
        static bool IsLeftMouseButtonPressed();
        static bool IsRightMouseButtonPressed();
        static bool IsMiddleMouseButtonPressed();
        static bool IsXButton1Pressed();
        static bool IsXButton2Pressed();
        static bool IsLeftMouseButtonReleased();
        static bool IsRightMouseButtonReleased();
        static bool IsMiddleMouseButtonReleased();
        static bool IsXButton1Released();
        static bool IsXButton2Released();
        static bool IsLeftMouseButtonHeld();
        static bool IsRightMouseButtonHeld();
        static bool IsMiddleMouseButtonHeld();
        static bool IsXButton1Held();
        static bool IsXButton2Held();
        static void Update();
        static void Destroy();
    };
}

#endif
