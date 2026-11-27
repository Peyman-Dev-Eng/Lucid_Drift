/*
 * Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */

#include "PointHitTesting.h"

bool LDDrift::PointHitTesting::PointInValidRange(
    const LDDrift::VecPos2D& targetPoint,
    const std::pair<LDDrift::VecPos2D, LDDrift::VecPos2D>& pointsOfLine) {
    return (targetPoint.Y > pointsOfLine.first.Y)
        != (targetPoint.Y > pointsOfLine.second.Y);
}

bool LDDrift::PointHitTesting::pointHitTesting(
    const LDDrift::VecPos2D& targetPoint,
    const std::pmr::vector<LDDrift::VecPos2D>& pointsOfTargetShape) {
    const std::size_t shapePointCount = pointsOfTargetShape.size();
    bool pointInsideShape = false;
    for (std::size_t currentPoint = 0; currentPoint < shapePointCount;
         ++currentPoint) {
        const std::size_t previousPoint
            = currentPoint == 0 ? shapePointCount - 1 : currentPoint - 1;
        if (!LDDrift::PointHitTesting::PointInValidRange(
            targetPoint, {
                pointsOfTargetShape[currentPoint],
                pointsOfTargetShape[previousPoint]
            })) {
            continue;
        }
        const float distanceFromCurrentLinePoints = pointsOfTargetShape[currentPoint].Y - pointsOfTargetShape[
            previousPoint].Y;
        const float distanceFromTargetPointToFirstPointOfLine = targetPoint.Y - pointsOfTargetShape[previousPoint].Y;
        const float targetPathProgress = distanceFromTargetPointToFirstPointOfLine / distanceFromCurrentLinePoints;

        const float xDistanceFromLinePoints = std::abs(
            pointsOfTargetShape[previousPoint].X - pointsOfTargetShape[currentPoint].X);

        if (const float intersectionX_Position = pointsOfTargetShape[previousPoint].X + (xDistanceFromLinePoints *
                targetPathProgress);
            targetPoint.X < intersectionX_Position) {
            pointInsideShape = !pointInsideShape;
        }
    }
    return pointInsideShape;
}
