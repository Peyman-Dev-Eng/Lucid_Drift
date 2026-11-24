// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

#include <stdlib.h>
#include <System/Core/Core.h>
#include <SubSystems/Logger/Logger.h>

int main() {
    LDDrift::Core core;
    core.Begin();
    core.EngineHandler();
    core.End();
    return EXIT_SUCCESS;
}
