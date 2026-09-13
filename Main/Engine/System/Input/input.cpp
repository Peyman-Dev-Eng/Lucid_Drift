#include "input.h"

void OpenFileInputEvent() {
    FileInputEvent = open("/dev/input/by-id/usb-SEMICO_USB_Keyboard-event-kbd", O_RDONLY | O_NONBLOCK);
    COF_assert(FileInputEvent != -1)

    constexpr IsKeyPressedInFrame Default = {.Before = false, .Current = false};
    for (uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        keyboard.Append(Default);
    }
    for (uint KeyCode = 0; KeyCode < 3; ++KeyCode) {
        mouse.Append(Default);
    }
}

void CloseFileInputEvent() {
    close(FileInputEvent);
}


void input::Keyboard::GetKeyInputEvent() {
#ifdef _WIN32
    return;
#elifdef __linux__
    input_event event{};
    while (true) {
        if (read(FileInputEvent, &event, sizeof(input_event)) != NO_EVENT_IS_AVAILABLE_TO_READ) {
            if (event.type == EV_KEY) {
                if (event.value == 0) {
                    keyboard[event.code].Current = false;
                } else if (event.value == 1) {
                    keyboard[event.code].Current = true;
                }
            }
        } else {
            break;
        }
    }

#endif
}

bool input::Keyboard::IsKeyPressed(const uint key) {
    GLB_assert(key >= 0 && key <= 125);
    return ((keyboard[key].Current == true) && (keyboard[key].Before == false));
}

bool input::Keyboard::IsKeyHeld(const uint key) {
    GLB_assert(key >= 0 && key <= 125);
    return ((keyboard[key].Current == true) && (keyboard[key].Before == true));
}

bool input::Keyboard::IsKeyReleased(const uint key) {
    GLB_assert(key >= 0 && key <= 125);
    return ((keyboard[key].Current == false) && (keyboard[key].Before == true));
}

Vector<uint> input::Keyboard::GetKeyPressed() {
    Vector<uint> KeyCodes;
    for (uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (keyboard[KeyCode].Current == true && keyboard[KeyCode].Before == false) {
            KeyCodes.Append(KeyCode);
        }
    }
    return KeyCodes;
}

Vector<uint> input::Keyboard::GetKeyHeld() {
    Vector<uint> KeyCodes;
    for (uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (keyboard[KeyCode].Current == true && keyboard[KeyCode].Before == true) {
            KeyCodes.Append(KeyCode);
        }
    }
    return KeyCodes;
}

Vector<uint> input::Keyboard::GetKeyReleased() {
    Vector<uint> KeyCodes;
    for (uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        if (keyboard[KeyCode].Current == false && keyboard[KeyCode].Before == true) {
            KeyCodes.Append(KeyCode);
        }
    }
    return KeyCodes;
}

void input::Keyboard::Update() {
    bool CanMouseUpdate = true;
    for (uint KeyCode = 0; KeyCode <= 125; ++KeyCode) {
        keyboard[KeyCode].Before = keyboard[KeyCode].Current;
        keyboard[KeyCode].Current = keyboard[KeyCode].Before ? true : false;
        if (CanMouseUpdate) {
            mouse[KeyCode].Before = mouse[KeyCode].Current;
            mouse[KeyCode].Current = mouse[KeyCode].Before ? true : false;
            KeyCode == 2 ? CanMouseUpdate = false : CanMouseUpdate = true;
        }
    }
}
