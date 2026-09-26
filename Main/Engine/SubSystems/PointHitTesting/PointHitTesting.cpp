#include "PointHitTesting.h"

bool LDDrift::PointHitTesting::PointInValidRange(const LDDrift::VecPos2D& targetPoint,
                                                 const std::pair<LDDrift::VecPos2D, LDDrift::VecPos2D>& pointsOfLine) {
    return (targetPoint.Y > pointsOfLine.first.Y) != (targetPoint.Y > pointsOfLine.second.Y);
}

bool LDDrift::PointHitTesting::pointHitTesting(const LDDrift::VecPos2D& targetPoint,
                                               const std::vector<LDDrift::VecPos2D>& pointsOfTargetShape) {
    const std::size_t shapePointCount = pointsOfTargetShape.size();
    bool pointInsideShape = false;
    for (std::size_t currentPoint = 0; currentPoint < shapePointCount; ++currentPoint) {
        const std::size_t previousPoint = currentPoint == 0 ? shapePointCount - 1 : currentPoint - 1;
        if (!LDDrift::PointHitTesting::PointInValidRange(targetPoint, {
                                                             pointsOfTargetShape[currentPoint],
                                                             pointsOfTargetShape[previousPoint]
                                                         })) {
            continue;
        }
        const float distanceFromCurrentLinePoints = pointsOfTargetShape[currentPoint].Y - pointsOfTargetShape[
            previousPoint].Y;
        const float distanceFromTargetPointToFirstPointOfLine = targetPoint.Y - pointsOfTargetShape[previousPoint].Y;
        float targetPathProgress = distanceFromTargetPointToFirstPointOfLine / distanceFromCurrentLinePoints;

        const float xDistanceFromLinePoints = std::abs(
            pointsOfTargetShape[previousPoint].X - pointsOfTargetShape[currentPoint].X);

        if (const float intersectionX_Position =
            pointsOfTargetShape[previousPoint].X + (xDistanceFromLinePoints * targetPathProgress);
            targetPoint.X < intersectionX_Position) {
            pointInsideShape = !pointInsideShape;
        } else {
            continue;
        }
    }
    return pointInsideShape;
}
