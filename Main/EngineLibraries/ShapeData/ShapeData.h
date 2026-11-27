#ifndef LUCID_DRIFT_SHAPEDATA_H
#define LUCID_DRIFT_SHAPEDATA_H
#include <vector>
#include <VecCol.h>
#include <VecPos2D.h>

namespace LDDrift
{
    enum class JoinLineType : long long int
    {
        Miter = 2147483647,
        Round = 4294967291,
        Bevel = 9999999967,
        Null = -1
    };

    class ShapeData
    {
    private:
        struct Vertex
        {
            float x, y, z;
        };

    public:
        std::pmr::vector<Vertex> Vertices;
        std::pmr::vector<VecCol> PointsColors;
        ShapeData();
        ShapeData(const std::pmr::vector<LDDrift::VecPos2D>& vertices, const std::pmr::vector<LDDrift::VecCol>& points_colors);
        ~ShapeData();
    };
}

#endif
