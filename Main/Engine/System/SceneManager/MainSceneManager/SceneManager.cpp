#include "SceneManager.h"

#include "System/Core/Core.h"

LDDrift::SceneManager::SceneManager() = default;

LDDrift::SceneManager::~SceneManager() = default;

void LDDrift::SceneManager::Initialize() {
    indexOfScene = 0;
    currentScene = nullptr;
    core = nullptr;
    scenes.reserve(3);
    CreateDefaultScene();
}

void LDDrift::SceneManager::CreateDefaultScene() {
    defaultScene.SetCorePTR(core);
    defaultScene.SetRendererPTR(&core->shape_render);
    defaultScene.SetTextureRendererPTR(&core->textureRender);
}

void LDDrift::SceneManager::ChangeScene(const LDDrift::ChangeSceneMode& mode) {
    if (mode == LDDrift::ChangeSceneMode::Suddenly) {
        // not available this page ( in process )
        return;
    } else if (mode == LDDrift::ChangeSceneMode::Smooth) {
        sceneAnimation.SmoothAlgorithm(nullptr, nullptr);
    } else if (mode == LDDrift::ChangeSceneMode::WindFromLeftToRight) {
        sceneAnimation.WindFromLeftToRightAlgorithm();
    } else if (mode == LDDrift::ChangeSceneMode::WindFromRightToLeft) {
        sceneAnimation.WindFromRightToLeftAlgorithm();
    } else if (mode == LDDrift::ChangeSceneMode::WindFromTopToBottom) {
        sceneAnimation.WindFromTopToBottomAlgorithm();
    } else if (mode == LDDrift::ChangeSceneMode::WindFromBottomToTop) {
        sceneAnimation.WindFromBottomToTopAlgorithm();
    }
}
