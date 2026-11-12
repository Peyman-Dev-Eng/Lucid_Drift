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
    defaultScene.SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double { return sceneAnimation.GetAnimationProcess(); }));
    currentScene = &defaultScene;
}

void LDDrift::SceneManager::ChangeScene(const LDDrift::ChangeSceneMode& mode) {
    if (mode == LDDrift::ChangeSceneMode::Suddenly) {
        sceneAnimation.SuddenlyAlgorithm(scenes[indexOfScene].scene, scenes[updateIndexOfScene()].scene);
    } else if (mode == LDDrift::ChangeSceneMode::Smooth) {
        sceneAnimation.SmoothAlgorithm(scenes[indexOfScene].scene, scenes[updateIndexOfScene()].scene);
    }
}

LDDrift::Scene* LDDrift::SceneManager::GetCurrentScene() const {
    return currentScene;
}

void LDDrift::SceneManager::CreateNewScene(const std::string& name) {
    LDDrift::Scene* newScene = new LDDrift::Scene();
    newScene->SetCorePTR(core);
    newScene->SetRendererPTR(&core->shape_render);
    newScene->SetTextureRendererPTR(&core->textureRender);
    newScene->SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double
    {
        return sceneAnimation.GetAnimationProcess();
    }));
    scenes.push_back({name, newScene});
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
    } catch (const std::runtime_error& e) {
        std::cout << "scenes is empty | We were attempting to divide a number by 0. log: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return indexOfScene;
}

void LDDrift::SceneManager::DeleteScene(const std::string& name) {
    int counter = 0;
    for (const auto& scene : scenes) {
        if (scene.name == name) {
            scenes.erase(scenes.begin() + counter);
            break;
        }
        ++counter;
    }
}

bool LDDrift::SceneManager::FindScene(const std::string& name) {
    if (name == "") {
        std::cout << "name scene entered is not available";
        return false;
    }
    for (const auto& scene : scenes) {
        if (scene.name == name) {
            return true;
        }
    }
    return false;
}

int LDDrift::SceneManager::GetSceneIndex(const std::string& name) {
    int counter = 0;
    for (const auto& scene : scenes) {
        if (scene.name == name) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

void LDDrift::SceneManager::ChangeScene(const std::string& name) {
    if (int indexOfScene = GetSceneIndex(name); indexOfScene != -1 ) {
        currentScene = scenes[indexOfScene].scene;
    }
}
