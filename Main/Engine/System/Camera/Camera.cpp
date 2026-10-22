#include "Camera.h"
#include <System/Core/Core.h>

LDDrift::Camera::Camera() = default;

LDDrift::Camera::~Camera() = default;

void LDDrift::Camera::InitializeCameraSystem(LDDrift::Core* corePTR) {
    core = corePTR;
    position = core->window.GetViewportSize() / 2;
    rotation = 0;
    zoom = 1.0f;
}

glm::mat4 LDDrift::Camera::GetViewMatrix() const {
    glm::mat4 view(1.0f);

    view = glm::rotate(
        view,
        -rotation,
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    view = glm::translate(
        view,
        glm::vec3(glm::vec2(-position.X, -position.Y), 0.0f)
    );

    return view;
}

glm::mat4 LDDrift::Camera::GetProjectionMatrix(float viewportWidth, float viewportHeight) const {
    const float halfWidth =
        viewportWidth / (2.0f * zoom);

    const float halfHeight =
        viewportHeight / (2.0f * zoom);

    return glm::ortho(
        -halfWidth,
        halfWidth,
        -halfHeight,
        halfHeight,
        -1.0f,
        1.0f
    );
}

void LDDrift::Camera::MoveUp() {
    position.Y += zoom;
}

void LDDrift::Camera::MoveDown() {
    position.Y -= zoom;
}

void LDDrift::Camera::MoveLeft() {
    position.X -= zoom;
}

void LDDrift::Camera::MoveRight() {
    position.X += zoom;
}
