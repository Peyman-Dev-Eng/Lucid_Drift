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

#ifndef LUCID_DRIFT_CAMERA_H
#define LUCID_DRIFT_CAMERA_H
#include <VecPos2D.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Actors/Shapes/MainShape/Shape.h>

namespace LDDrift
{
    class Core;

    class Camera
    {
    private:
        struct ShapeFollowing
        {
            LDDrift::Actors::Shape* targetShape = nullptr;
            bool isEqualCameraPositionAndShapePos = false;
        };

        ShapeFollowing shapeFollowing;

        LDDrift::Core* core = nullptr;
        LDDrift::VecPos2D position;
        float rotation = 0.0f; // In radians
        float zoom = 1;
        float speed = 10;

    public:
        Camera();
        ~Camera();
        void FallowTargetShape();
        void SetTargetShape(LDDrift::Actors::Shape* targetShape_ptr);
        void SetSpeedCamera(float speed_v);
        void SetZoomCamera(float zoom_v);
        void AddZoomCamera(float addZoom_v);
        void SubZoomCamera(float subZoom_v);
        void AddSpeedCamera(float addSpeed_v);
        void SubSpeedCamera(float subSpeed_v);
        void InitializeCameraSystem(LDDrift::Core* corePTR);
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const;
        [[nodiscard]] float GetZoom() const;
        [[nodiscard]] float GetSpeed() const;
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
    };
} // LDDrift

#endif
