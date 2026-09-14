#include <iostream>
#include <thread>
#include "Main/Engine/System/Input/input.h"

int main() {
    input::Keyboard::init();
    while (true) {
        input::Keyboard::GetKeyInputEvent();
        if (input::Keyboard::IsKeyPressed(static_cast<long int>(LinuxKeyCode::Key_ESC))) {
            break;
        }
        if (input::Keyboard::IsKeyPressed(static_cast<long int>(LinuxKeyCode::Key_W))) {
            std::cout << "W" << std::endl;
        }
        if (input::Keyboard::IsKeyPressed(static_cast<long int>(LinuxKeyCode::Key_A))) {
            std::cout << "A" << std::endl;
        }
        if (input::Keyboard::IsKeyPressed(static_cast<long int>(LinuxKeyCode::Key_S))) {
            std::cout << "S" << std::endl;
        }
        if (input::Keyboard::IsKeyPressed(static_cast<long int>(LinuxKeyCode::Key_D))) {
            std::cout << "D" << std::endl;
        }
        if (input::Keyboard::IsKeyHeld(static_cast<long int>(LinuxKeyCode::Key_F))) {
            std::cout << "F" << std::endl;
        }
        if (input::Keyboard::IsKeyReleased(static_cast<long int>(LinuxKeyCode::Key_R))) {
            std::cout << "R" << std::endl;
        }
        input::Keyboard::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    return 0;
}
