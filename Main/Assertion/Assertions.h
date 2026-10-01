#ifndef LUCID_DRIFT_ASSERTIONS_H
#define LUCID_DRIFT_ASSERTIONS_H
#include <iostream>
#include <string>
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET "\033[0m"

namespace LDDrift::Assertions
{
    [[noreturn]] void PrintLog(const char* condition, const char* file, int line, const char* function, const char* message);
}

// global assert
#define GLB_assert(cond) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, nullptr);

// can`t open file assert
#define COF_assert(cond) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, "can not open file");

// not available os assert
#define NAO_assert(cond) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, "our engine does not support your operating system.");

// out of range assert
#define OOR_assert(cond) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, "value is out of range");

// custom message assert
#define CTM_assert(cond, msg) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, msg);

// null pointer value assert
#define NPV_assert(cond) \
    cond ? (void)0 : LDDrift::Assertions::PrintLog(#cond, __FILE__, __LINE__, __func__, "pointer is null" );

#endif
