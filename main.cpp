#include <iostream>
#include <thread>
#include "Main/Engine/System/Input/input.h"


int main() {
    input::Mouse::Init();
    while (true) {
        input::Mouse::GetMouseInputEvent();
        if (input::Mouse::IsLeftMouseButtonPressed()) {
            std::cout << "LeftButtonPressed" << std::endl;
        }
        if (input::Mouse::IsLeftMouseButtonHeld()) {
            std::cout << "LeftButtonHeld" << std::endl;
        }
        if (input::Mouse::IsLeftMouseButtonReleased()) {
            std::cout << "LeftButtonReleased" << std::endl;
        }
        if (input::Mouse::IsRightMouseButtonPressed()) {
            break;
        }
        input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    input::Mouse::Destroy();
    return 0;
}
