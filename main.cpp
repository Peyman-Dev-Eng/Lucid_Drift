#include <System/Core/Core.h>
#include <SubSystems/Logger/Logger.h>

int main() {
    LDDrift::Core core;
    core.Begin();
    core.EngineHandler();
    core.End();
    return 0;
}
