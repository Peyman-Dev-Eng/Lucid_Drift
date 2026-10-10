#ifndef LUCID_DRIFT_INPUT_H
#define LUCID_DRIFT_INPUT_H

#define NOT_AVAILABLE_OS 0
#include <vector>
#include <unordered_map>
#include <Assertions.h>
#include <array>
#include <algorithm>
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


inline std::vector<LD_uint> ToUpdateValues;


#ifdef _WIN32
#include <windows.h>
inline std::array<IsKeyPressedInFrame, 256> WindowsKeyCodes;

#elifdef __linux__
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#define NO_EVENT_IS_AVAILABLE_TO_READ (-1)

namespace LDDrift
{
    namespace Event::Mouse
    {
        enum class WindowsMouseKeyCode : LD_uint
        {
            LeftButton = static_cast<LD_lint>(0x01),
            RightButton = static_cast<LD_lint>(0x02),
            MiddleButton = static_cast<LD_lint>(0x04),
            XButton1 = static_cast<LD_lint>(0x05),
            XButton2 = static_cast<LD_lint>(0x06)
        };

        enum class LinuxMouseKeyCode : LD_uint
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
        enum class LinuxKeyboardKeyCode : LD_uint
        {
            Key_RESERVED = 0,
            Key_ESC = 1,
            Key_1 = 2,
            Key_2 = 3,
            Key_3 = 4,
            Key_4 = 5,
            Key_5 = 6,
            Key_6 = 7,
            Key_7 = 8,
            Key_8 = 9,
            Key_9 = 10,
            Key_0 = 11,
            Key_MINUS = 12,
            Key_EQUALS = 13,
            Key_BACKSPACE = 14,
            Key_TAB = 15,
            Key_Q = 16,
            Key_W = 17,
            Key_E = 18,
            Key_R = 19,
            Key_T = 20,
            Key_Y = 21,
            Key_U = 22,
            Key_I = 23,
            Key_O = 24,
            Key_P = 25,
            Key_LBRACKET = 26,
            Key_RBRACKET = 27,
            Key_ENTER = 28,
            Key_LCONTROL = 29,
            Key_A = 30,
            Key_S = 31,
            Key_D = 32,
            Key_F = 33,
            Key_G = 34,
            Key_H = 35,
            Key_J = 36,
            Key_K = 37,
            Key_L = 38,
            Key_SEMICOLON = 39,
            Key_APOSTROPHE = 40,
            Key_GRAVE = 41,
            Key_LSHIFT = 42,
            Key_BACKSLASH = 43,
            Key_Z = 44,
            Key_X = 45,
            Key_C = 46,
            Key_V = 47,
            Key_B = 48,
            Key_N = 49,
            Key_M = 50,
            Key_COMMA = 51,
            Key_DOT = 52,
            Key_SLASH = 53,
            Key_RSHIFT = 54,
            Key_KPASTERISK = 55,
            Key_LALT = 56,
            Key_SPACE = 57,
            Key_CAPSLOCK = 58,
            Key_F1 = 59,
            Key_F2 = 60,
            Key_F3 = 61,
            Key_F4 = 62,
            Key_F5 = 63,
            Key_F6 = 64,
            Key_F7 = 65,
            Key_F8 = 66,
            Key_F9 = 67,
            Key_F10 = 68,
            Key_NUMLOCK = 69,
            Key_SCROLLLOCK = 70,
            Key_KP7 = 71,
            Key_KP8 = 72,
            Key_KP9 = 73,
            Key_KPMINUS = 74,
            Key_KP4 = 75,
            Key_KP5 = 76,
            Key_KP6 = 77,
            Key_KPPLUS = 78,
            Key_KP1 = 79,
            Key_KP2 = 80,
            Key_KP3 = 81,
            Key_KP0 = 82,
            Key_KPDOT = 83,

            Key_RESERVED_84 = 84,

            Key_ZENKAKUHANKAKU = 85,
            Key_102ND = 86,
            Key_F11 = 87,
            Key_F12 = 88,
            Key_RO = 89,
            Key_KATAKANA = 90,
            Key_HIRAGANA = 91,
            Key_HENKAN = 92,
            Key_KATAKANAHIRAGANA = 93,
            Key_MUHENKAN = 94,
            Key_KPJPCOMMA = 95,
            Key_KPENTER = 96,
            Key_RCONTROL = 97,
            Key_KPSLASH = 98,
            Key_SYSRQ = 99,
            Key_RALT = 100,
            Key_LINEFEED = 101,
            Key_HOME = 102,
            Key_UP = 103,
            Key_PAGEUP = 104,
            Key_LEFT = 105,
            Key_RIGHT = 106,
            Key_END = 107,
            Key_DOWN = 108,
            Key_PAGEDOWN = 109,
            Key_INSERT = 110,
            Key_DELETE = 111,
            Key_MACRO = 112,
            Key_MUTE = 113,
            Key_VOLUMEDOWN = 114,
            Key_VOLUMEUP = 115,
            Key_POWER = 116,
            Key_KPEQUAL = 117,
            Key_KPPLUSMINUS = 118,
            Key_PAUSE = 119,
            Key_SCALE = 120,
            Key_KPCOMMA = 121,
            Key_HANGEUL = 122,
            Key_HANJA = 123,
            Key_YEN = 124,
            Key_LMETA = 125,
            Key_RMETA = 126,
            Key_COMPOSE = 127,
            Key_STOP = 128,
            Key_AGAIN = 129,
            Key_PROPS = 130,
            Key_UNDO = 131,
            Key_FRONT = 132,
            Key_COPY = 133,
            Key_OPEN = 134,
            Key_PASTE = 135,
            Key_FIND = 136,
            Key_CUT = 137,
            Key_HELP = 138,
            Key_MENU = 139,
            Key_CALC = 140,
            Key_SETUP = 141,
            Key_SLEEP = 142,
            Key_WAKEUP = 143,
            Key_FILE = 144,
            Key_SENDFILE = 145,
            Key_DELETEFILE = 146,
            Key_XFER = 147,
            Key_PROG1 = 148,
            Key_PROG2 = 149,
            Key_WWW = 150,
            Key_MSDOS = 151,
            Key_COFFEE = 152,
            Key_ROTATE_DISPLAY = 153,
            Key_CYCLEWINDOWS = 154,
            Key_MAIL = 155,
            Key_BOOKMARKS = 156,
            Key_COMPUTER = 157,
            Key_BACK = 158,
            Key_FORWARD = 159,
            Key_CLOSECD = 160,
            Key_EJECTCD = 161,
            Key_EJECTCLOSECD = 162,
            Key_NEXTSONG = 163,
            Key_PLAYPAUSE = 164,
            Key_PREVIOUSSONG = 165,
            Key_STOPCD = 166,
            Key_RECORD = 167,
            Key_REWIND = 168,
            Key_PHONE = 169,
            Key_ISO = 170,
            Key_CONFIG = 171,
            Key_HOMEPAGE = 172,
            Key_REFRESH = 173,
            Key_EXIT = 174,
            Key_MOVE = 175,
            Key_EDIT = 176,
            Key_SCROLLUP = 177,
            Key_SCROLLDOWN = 178,
            Key_KPLEFTPAREN = 179,
            Key_KPRIGHTPAREN = 180,
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

    inline std::vector<std::string> KeyBoardKeyName;


#endif

    inline std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> TargetKeys;

    namespace input
    {
        /**
         * @class Keyboard
         * @brief Manages keyboard input events and provides utility functions to query the state of keyboard keys.
         *
         * This class provides functionalities to initialize, update, and query the state of keyboard keys.
         * It supports both Windows and Linux platforms, handling different input mechanisms on each.
         * Key functionalities include setting target keys, checking key states (pressed, held, released),
         * and retrieving lists of pressed, held, and released keys.
         *
         * @note The class uses platform-specific implementations for handling keyboard input events.
         * It also includes utility functions to identify if a key corresponds to a character.
         *
         * @see Mouse
         */
        class Keyboard
        {
        private:
            static bool InputIsChar(const LD_lint& target);

        public:
            static void Init();
            static void SetKeyTarget(const std::vector<Event::Keyboard::LinuxKeyboardKeyCode>& keys);
            static void GetKeyInputEvent();
            static bool IsKeyPressed(Event::Keyboard::LinuxKeyboardKeyCode key);
            static bool IsKeyHeld(Event::Keyboard::LinuxKeyboardKeyCode key);
            static bool IsKeyReleased(Event::Keyboard::LinuxKeyboardKeyCode key);
            static std::vector<Event::Keyboard::LinuxKeyboardKeyCode> GetKeyPressed();
            static std::vector<Event::Keyboard::LinuxKeyboardKeyCode> GetKeyHeld();
            static std::vector<Event::Keyboard::LinuxKeyboardKeyCode> GetKeyReleased();
            static void Update();
            static void Destroy();
        };

        /**
         * @class Mouse
         * @brief Manages mouse input events and provides utility functions to query the state of mouse buttons and cursor position.
         *
         * This class provides functionalities to initialize, update, and query the state of mouse buttons and cursor position.
         * It supports both Windows and Linux platforms, handling different input mechanisms on each.
         * Key functionalities include setting target keys, checking button states (pressed, held, released),
         * and retrieving the current cursor position.
         *
         * @note The class uses platform-specific implementations for handling mouse input events.
         *
         * @see Keyboard
         */
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
}

inline std::vector<LDDrift::Event::Keyboard::LinuxKeyboardKeyCode> TargetKeys;
#endif
