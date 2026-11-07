#include "SceneManager.h"

#include "System/Core/Core.h"

LDDrift::SceneManager::SceneManager() = default;

LDDrift::SceneManager::~SceneManager() = default;

void LDDrift::SceneManager::Initialize() {
    indexOfScene = 0;
    scenes.reserve(3);
    CreateDefaultScene();
}

void LDDrift::SceneManager::CreateDefaultScene() {
    defaultScene.SetCorePTR(core);
    defaultScene.SetRendererPTR(&core->shape_render);
    defaultScene.SetTextureRendererPTR(&core->textureRender);
    currentScene = &defaultScene;
}

void LDDrift::SceneManager::ChangeScene(const LDDrift::ChangeSceneMode& mode) {
    if (mode == LDDrift::ChangeSceneMode::Suddenly) {
        sceneAnimation.SuddenlyAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    } else if (mode == LDDrift::ChangeSceneMode::Smooth) {
        sceneAnimation.SmoothAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    } else if (mode == LDDrift::ChangeSceneMode::WindFromLeftToRight) {
        sceneAnimation.WindFromLeftToRightAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    } else if (mode == LDDrift::ChangeSceneMode::WindFromRightToLeft) {
        sceneAnimation.WindFromRightToLeftAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    } else if (mode == LDDrift::ChangeSceneMode::WindFromTopToBottom) {
        sceneAnimation.WindFromTopToBottomAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    } else if (mode == LDDrift::ChangeSceneMode::WindFromBottomToTop) {
        sceneAnimation.WindFromBottomToTopAlgorithm(scenes[indexOfScene], scenes[updateIndexOfScene()]);
    }
}

LDDrift::Scene* LDDrift::SceneManager::GetCurrentScene() const {
    return currentScene;
}

void LDDrift::SceneManager::CreateNewScene() {
    LDDrift::Scene* newScene = new LDDrift::Scene();
    newScene->SetCorePTR(core);
    newScene->SetRendererPTR(&core->shape_render);
    newScene->SetTextureRendererPTR(&core->textureRender);
    newScene->SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double
    {
        return sceneAnimation.GetAnimationProcess();
    }));
    scenes.push_back(new LDDrift::Scene());
}

void LDDrift::SceneManager::SetCorePTR(LDDrift::Core* core_ptr) {
    core = core_ptr;
}

LDDrift::Scene& LDDrift::SceneManager::GetDefaultScene() {
    return defaultScene;
}

std::size_t LDDrift::SceneManager::updateIndexOfScene() {
    try {
        if (scenes.empty()) {
            throw std::runtime_error("zero division error");
        }
        indexOfScene = (indexOfScene + 1) % scenes.size();
    } catch(const std::runtime_error& e) {
        std::cout << "scenes is empty | We were attempting to divide a number by 0. log: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return indexOfScene;
}
