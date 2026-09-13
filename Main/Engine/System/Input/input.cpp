#include "input.h"

void OpenFileInputEvent() {
    FileInputEvent = -1;

}


void input::Keyboard::GetKeyInputEvent() {
#ifdef _WIN32
    return;
#elifdef __linux__
#else
    assert(false)
#endif
}
