#ifndef LUCID_DRIFT_SHAPEDATA_H
#define LUCID_DRIFT_SHAPEDATA_H
#include <vector>
#include <VecCol.h>
#include <VecPos.h>

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
        ShapeData(const std::vector<LDDrift::VecPos2D>& vertices, const std::vector<LDDrift::VecCol>& points_colors);
        ~ShapeData();
    };
}

#endif
