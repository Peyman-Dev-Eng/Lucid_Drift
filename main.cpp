#include <System/Core/Core.h>

int main() {
    std::cout << "Hello World" << std::endl;
    LDDrift::Core core;
    core.Begin();
    core.EngineHandler();
    core.End();
    return 0;
}
