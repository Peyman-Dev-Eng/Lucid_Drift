#ifndef LUCID_DRIFT_SHAPEDATA_H
#define LUCID_DRIFT_SHAPEDATA_H
#include <vector>
#include <VecCol.h>

namespace LDDrift
{
    class ShapeData
    {
    private:
        struct Vertex
        {
            float x, y, z;
        };
    public:
        std::vector<Vertex> Vertices;
        std::vector<VecCol> PointsColors;
        ShapeData();
        ShapeData(const std::vector<Vertex>& vertices, const std::vector<VecCol>& points_colors);
        ~ShapeData();
    };
}

#endif
