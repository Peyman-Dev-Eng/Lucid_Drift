#include "ShapeData.h"

LDDrift::ShapeData::ShapeData() = default;

LDDrift::ShapeData::ShapeData(const std::vector<Vertex>& vertices, const std::vector<VecCol>& points_colors) {
    Vertices = vertices;
    PointsColors = points_colors;
}

LDDrift::ShapeData::~ShapeData() = default;
