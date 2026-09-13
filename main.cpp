#include <iostream>
#include <Vector.h>
#include "Main/Engine/System/Input/input.h"

auto SUM(auto a, auto b) {
    return a + b;
}

int main() {
    std::cout << typeid(SUM(1, 3.2)) == typeid(float) ? 1 : 0 << std::endl;
    std::cout << SUM(10, 20) << std::endl;
    return 0;
}
