#include "Camera.h"
#include <System/Core/Core.h>

void LDDrift::Camera::MoveUp() {
    position.Y += speed;
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveDown() {
    position.Y -= speed;
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveLeft() {
    position.X -= speed;
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveRight() {
    position.X += speed;
    core->render.UpdateViewMatrix();
}

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

glm::mat4 LDDrift::Camera::GetProjectionMatrix(const float viewportWidth, const float viewportHeight) const {
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

void LDDrift::Camera::SetSpeedCamera(const float speed_v) {
    speed = speed_v;
}

void LDDrift::Camera::AddSpeedCamera(const float addSpeed_v) {
    speed += addSpeed_v;
}

void LDDrift::Camera::SubSpeedCamera(const float subSpeed_v) {
    if ((speed - subSpeed_v) < 0) {
        speed = 0;
        return;
    }
    speed -= subSpeed_v;
}

void LDDrift::Camera::AddZoomCamera(const float addZoom_v) {
    zoom += addZoom_v;
}

void LDDrift::Camera::SubZoomCamera(const float subZoom_v) {
    if ((zoom - subZoom_v) < 0.1f) {
        zoom = 0.1f;
        return;
    }
    zoom -= subZoom_v;
}

float LDDrift::Camera::GetSpeed() const {
    return speed;
}

float LDDrift::Camera::GetZoom() const {
    return zoom;
}

void LDDrift::Camera::SetZoomCamera(const float zoom_v) {
    zoom = zoom_v;
}
