#ifndef LUCID_DRIFT_POLYGON_H
#define LUCID_DRIFT_POLYGON_H
#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    class Polygon final : public LDDrift::Actors::Shape
    {
    public:
        Polygon();
        [[nodiscard]] LDDrift::VecCol CalculateAverageVertexColor() const override;
        void Rebuild() override;
        ~Polygon() override;
    };
}

#endif
