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
        float zoom = 1.0f;

    public:
        Camera();
        ~Camera();
        void InitializeCameraSystem(LDDrift::Core* corePTR);
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix(float viewportWidth, float viewportHeight) const;
    };
} // LDDrift

#endif
