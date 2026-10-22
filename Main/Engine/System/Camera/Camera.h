#ifndef LUCID_DRIFT_CAMERA_H
#define LUCID_DRIFT_CAMERA_H
#include <VecPos.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LDDrift
{
    class Core;

    class Camera
    {
    private:
        LDDrift::Core* core = nullptr;
        LDDrift::VecPos2D position;
        float rotation = 0.0f; // In radians
        float zoom = 1;
        float speed = 1;

    public:
        Camera();
        ~Camera();
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
