#ifndef LUCID_DRIFT_CAMERA_H
#define LUCID_DRIFT_CAMERA_H
#include <VecPos.h>
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
