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

            Vertex(const VecPos2D& pos) {
                x = pos.X;
                y = pos.Y;
                z = 0.0f;
            }
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
