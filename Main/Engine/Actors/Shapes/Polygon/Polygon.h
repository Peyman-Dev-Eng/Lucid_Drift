#ifndef LUCID_DRIFT_POLYGON_H
#define LUCID_DRIFT_POLYGON_H
#include "../MainShape/Shape.h"

namespace LDDrift::Actors
{
    class Polygon : public LDDrift::Actors::Shape
    {
    private:
    public:
        Polygon();
        ~Polygon() override;
    };
}

#endif
