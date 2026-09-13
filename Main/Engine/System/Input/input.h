#ifndef LUCID_DRIFT_INPUT_H
#define LUCID_DRIFT_INPUT_H
#include <HashMap.h>

#ifdef _WIN32
#include <windows.h>

#elifdef __linux__
#include <linux/input.h>

#endif




namespace input
{
    class Keyboard {};

    class Mouse {};
}


#endif
