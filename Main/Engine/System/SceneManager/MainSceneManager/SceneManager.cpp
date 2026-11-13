#include "SceneManager.h"

#include "System/Core/Core.h"

LDDrift::SceneManager::SceneManager() = default;

LDDrift::SceneManager::~SceneManager() = default;

void LDDrift::SceneManager::Initialize() {
    indexOfScene = 0;
    CreateDefaultScene();
}

void LDDrift::SceneManager::CreateDefaultScene() {
    defaultScene.SetCorePTR(core_ptr);
    defaultScene.SetRendererPTR(shapeRender_ptr);
    defaultScene.SetTextureRendererPTR(textureRender_ptr);
    defaultScene.SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double
    {
        return sceneAnimation.GetAnimationProcess();
    }));
    currentScene = &defaultScene;
}

void LDDrift::SceneManager::ChangeScene(const LDDrift::ChangeSceneMode& mode) {
    if (mode == LDDrift::ChangeSceneMode::Suddenly) {
        try {
            sceneAnimation.SuddenlyAlgorithm(scenes[indexOfScene].scene, scenes[updateIndexOfScene()].scene);
        } catch (const std::runtime_error& e) {
            std::cout << "scenes size: " << scenes.size() << "    ---    " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } else if (mode == LDDrift::ChangeSceneMode::Smooth) {
        try {
            sceneAnimation.SmoothAlgorithm(scenes[indexOfScene].scene, scenes[updateIndexOfScene()].scene);
        } catch (const std::runtime_error& e) {
            std::cout << "scene size: " << scenes.size() << "    ---    " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

LDDrift::Scene* LDDrift::SceneManager::GetCurrentScene() const {
    return currentScene;
}

void LDDrift::SceneManager::CreateNewScene(const std::string& name) {
    LDDrift::Scene* newScene = new LDDrift::Scene();
    newScene->SetCorePTR(core_ptr);
    newScene->SetRendererPTR(shapeRender_ptr);
    newScene->SetTextureRendererPTR(textureRender_ptr);
    newScene->SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double
    {
        return sceneAnimation.GetAnimationProcess();
    }));
    scenes.push_back({.name = name, .scene = newScene});
}

void LDDrift::SceneManager::SetCorePTR(LDDrift::Core* _core_ptr) {
    core_ptr = _core_ptr;
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
    for (const auto& [sceneName, scene] : scenes) {
        if (sceneName == name) {
            scenes.erase(scenes.begin() + counter);
            break;
        }
        ++counter;
    }
}

bool LDDrift::SceneManager::FindScene(const std::string& name) const {
    if (name == "" || scenes.empty()) {
        return false;
    }
    for (const auto& [sceneName, scene] : scenes) {
        if (sceneName == name) {
            return true;
        }
    }
    return false;
}

int LDDrift::SceneManager::GetSceneIndex(const std::string& name) const {
    int counter = 0;
    for (const auto& [sceneName, scene] : scenes) {
        if (sceneName == name) {
            return counter;
        }
        ++counter;
    }
    return -1;
}

void LDDrift::SceneManager::ChangeScene(const std::string& name) {
    for (const auto& [sceneName, scene] : scenes) {
        if (sceneName == name) {
            currentScene = scene;
        }
    }
}

void LDDrift::SceneManager::SetTextureRendererPTR(LDDrift::TextureRender* texture_render_ptr) {
    textureRender_ptr = texture_render_ptr;
}

void LDDrift::SceneManager::SetShapeRenderPTR(LDDrift::ShapeRender* shape_render_ptr) {
    shapeRender_ptr = shape_render_ptr;
}
