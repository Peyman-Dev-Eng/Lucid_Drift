#ifndef LUCID_DRIFT_CODE_PATHFINDER_H
#define LUCID_DRIFT_CODE_PATHFINDER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <ranges>
#include <type_traits>
#define NULL_STRING "NULL"

namespace LDDrift
{
    class CodePathfinder final
    {
    private:
        std::string lastQuery;
        bool hasCachedQuery = false;
        std::vector<std::string> lastSuggestions;
        std::vector<std::string> KeyWords;
    public:
        CodePathfinder();
        ~CodePathfinder();
        void initializeCodePathfinder();
        std::vector<std::string> GetCodeSuggestions(const std::string& CodeSuggestion);
    };
} // LDDrift

#endif
