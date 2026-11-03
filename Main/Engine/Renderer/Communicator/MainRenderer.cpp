#include "MainRenderer.h"
#include <System/Core/Core.h>

LDDrift::MainRenderer::MainRenderer() = default;

LDDrift::MainRenderer::~MainRenderer() = default;

void LDDrift::MainRenderer::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

glm::mat4 LDDrift::MainRenderer::UpdateViewMatrix() const {
    const LDDrift::VecPos2D viewPortSize = core->window.GetViewportSize();
    const glm::mat4 viewProjection =
        core->camera.GetProjectionMatrix(viewPortSize.X, viewPortSize.Y) * core->camera.GetViewMatrix();
    return viewProjection;
}
