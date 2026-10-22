#include <System/Core/Core.h>

int main() {
    LDDrift::Core core;
    core.Begin();
    core.EngineHandler();
    return 0;
}
