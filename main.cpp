#include <iostream>
#include <thread>
#include "Main/Engine/System/Input/input.h"


int main() {
    GLB_assert(false);
    LDDrift::input::Mouse::Init();
    while (true) {
        LDDrift::input::Mouse::GetMouseInputEvent();
        if (LDDrift::input::Mouse::IsLeftMouseButtonPressed()) {
            std::cout << "LeftButtonPressed" << std::endl;
        }
        if (LDDrift::input::Mouse::IsLeftMouseButtonHeld()) {
            std::cout << "LeftButtonHeld" << std::endl;
        }
        if (LDDrift::input::Mouse::IsLeftMouseButtonReleased()) {
            std::cout << "LeftButtonReleased" << std::endl;
        }
        if (LDDrift::input::Mouse::IsRightMouseButtonPressed()) {
            break;
        }
        LDDrift::input::Mouse::Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LDDrift::input::Mouse::Destroy();
    return 0;
}
