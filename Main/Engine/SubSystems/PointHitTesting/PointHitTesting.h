#ifndef LUCID_DRIFT_POINTHITTESTING_H
#define LUCID_DRIFT_POINTHITTESTING_H
#include <VecPos.h>
#include <vector>

namespace LDDrift
{
    class PointHitTesting final
    {
    private:
        static bool PointInValidRange(const LDDrift::VecPos2D&, const std::pair<LDDrift::VecPos2D, LDDrift::VecPos2D>&);

    public:
        static bool pointHitTesting(const LDDrift::VecPos2D&, const std::vector<LDDrift::VecPos2D>&);
    };
}

#endif
