#include "Camera.h"
#include <System/Core/Core.h>

void LDDrift::Camera::MoveUp() {
    position.Y += (speed * LDDrift::func::GetDeltaTime());
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveDown() {
    position.Y -= (speed * LDDrift::func::GetDeltaTime());
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveLeft() {
    position.X -= (speed * LDDrift::func::GetDeltaTime());
    core->render.UpdateViewMatrix();
}

void LDDrift::Camera::MoveRight() {
    position.X += (speed * LDDrift::func::GetDeltaTime());
    core->render.UpdateViewMatrix();
}

LDDrift::Camera::Camera() = default;

LDDrift::Camera::~Camera() = default;

void LDDrift::Camera::InitializeCameraSystem(LDDrift::Core* corePTR) {
    core = corePTR;
    position = core->window.GetViewportSize() / 2;
    rotation = 0;
    zoom = 1.0f;
    speed = 50;
}

glm::mat4 LDDrift::Camera::GetViewMatrix() const {
    glm::mat4 view(1.0f);

    view = rotate(
        view,
        -rotation,
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    view = translate(
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

void LDDrift::Camera::SetTargetShape(LDDrift::Actors::Shape* targetShape_ptr) {
    shapeFollowing.targetShape = targetShape_ptr;
}

void LDDrift::Camera::FallowTargetShape() {
    if (shapeFollowing.targetShape == nullptr) {
        shapeFollowing.isEqualCameraPositionAndShapePos = false;
        return;
    }

    const LDDrift::VecPos2D& targetPosition =
        shapeFollowing.targetShape->GetOriginalPosition_global();

    const float _deltaTime = LDDrift::func::GetDeltaTime();
    const float step = std::max(0.0f, speed * _deltaTime);

    const float oldX = position.X;
    const float oldY = position.Y;

    const auto moveToward = [step](float& current, const float target) {
        const float delta = target - current;

        if (const float distance = std::abs(delta); distance <= step) {
            current = target;
        } else if (step > 0.0f) {
            current += std::copysign(step, delta);
        }
    };

    moveToward(position.X, targetPosition.X);
    moveToward(position.Y, targetPosition.Y);

    shapeFollowing.isEqualCameraPositionAndShapePos =
        position.X == targetPosition.X &&
        position.Y == targetPosition.Y;

    if (position.X != oldX || position.Y != oldY) {
        core->render.UpdateViewMatrix();
    }
}
