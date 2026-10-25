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
        std::vector<std::string> lastSuggestions;

        std::vector<std::string> LDDrift_keyWords;
        std::vector<std::string> std_keyWords;

    public:
        CodePathfinder();
        ~CodePathfinder();
        void initializeCodePathfinder();
        std::vector<std::string> GetSuggestions(const std::string& inputLineText);
    };
} // LDDrift

#endif
