/*
* Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */
#ifndef LUCID_DRIFT_CODE_PATHFINDER_H
#define LUCID_DRIFT_CODE_PATHFINDER_H
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <ranges>
#include <type_traits>
#define NULL_STRING "NULL_VALUE"

namespace LDDrift
{
    /**
     * @class CodePathfinder
     * @brief Provides suggestions based on the input code line.
     *
     * The CodePathfinder class is designed to analyze the input code line and suggest
     * relevant keywords or snippets based on the content. It maintains a history of
     * the last input and suggestions to optimize the suggestion process.
     *
     * @note This class is final and cannot be inherited.
     */
    class CodePathfinder final
    {
    private:
        std::string lastLineInput = NULL_STRING;
        std::pmr::vector<std::string> lastSuggestions;

        std::pmr::vector<std::string> LDDrift_keyWords;
        std::pmr::vector<std::string> std_keyWords;

    public:
        CodePathfinder();
        ~CodePathfinder();
        void initializeCodePathfinder();
        std::pmr::vector<std::string> GetSuggestions(const std::string& inputLineText);
    };
} // LDDrift

#endif
