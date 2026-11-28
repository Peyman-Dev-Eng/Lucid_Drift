// Copyright (C) 2026 Peyman
//
// This file is part of Lucid Drift.
// Lucid Drift is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// This software is distributed without any warranty.
// See the LICENSE file for the full license text.
// See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.

#include "SceneManager.h"
#include "System/Core/Core.h"

LDDrift::SceneManager::SceneManager() = default;

LDDrift::SceneManager::~SceneManager() = default;

void LDDrift::SceneManager::Initialize() {
    indexOfScene = 0;
    CreateDefaultScene();
}

void LDDrift::SceneManager::CreateDefaultScene() {
    if (!scenes.empty()) {
        return;
    }
    defaultScene.SetCorePTR(core_ptr);
    defaultScene.SetRendererPTR(shapeRender_ptr);
    defaultScene.SetTextureRendererPTR(textureRender_ptr);
    defaultScene.SetChangeColorFunction(static_cast<Scene::GetAnimationProgressFunction>([this]() -> double
    {
        return sceneAnimation.GetAnimationProcess();
    }));
    currentScene = &defaultScene;
    currentSceneName = "default";
}

bool LDDrift::SceneManager::ChangeScene(const LDDrift::ChangeSceneMode& mode) {
    if (mode == LDDrift::ChangeSceneMode::Suddenly) {
        try {
            textureRender_ptr->DeleteTextures();
            shapeRender_ptr->DeleteActors();
            sceneAnimation.SuddenlyAlgorithm(scenes[indexOfScene].scene,
                                             scenes[(indexOfScene + 1) % scenes.size()].scene);
        } catch (const LDDrift::EndAnimation& e) {
            updateIndexOfScene();
            // append textures to render system
            for (const auto& texture : scenes[indexOfScene].scene->textures) {
                if (texture.render) textureRender_ptr->AddTexture(texture.texture, 1);
            }
            // append circles to render system
            for (const auto& circle : scenes[indexOfScene].scene->circleShapes) {
                if (circle.render) shapeRender_ptr->AddShapeToRender(circle.circle);
            }
            // append polygons to render system
            for (const auto& polygon : scenes[indexOfScene].scene->polygonShapes) {
                if (polygon.render) shapeRender_ptr->AddShapeToRender(polygon.polygon);
            }
            // append lines actor to render system
            for (const auto& line : scenes[indexOfScene].scene->lines) {
                if (line.render) shapeRender_ptr->AddLineToRender(line.line);
            }
            currentScene = scenes[indexOfScene].scene;
            currentSceneName = scenes[indexOfScene].name;
            return true;
        } catch (const std::runtime_error& e) {
            LDDrift::Logger::ErrorLog("Engine", "Scene Manager",
                                      Log(std::string("scenes size: ") + std::to_string(scenes.size()) + "    ---    " +
                                          e.what(), LDDrift::LogType::ZeroDivideFailed));
            return false;
        } catch (const std::exception& e) {
            LDDrift::Logger::ErrorLog("Engine", "Scene Manager",
                                      Log(std::string("Error: ") + e.what(), LDDrift::LogType::Null));
            return false;
        }
    } else if (mode == LDDrift::ChangeSceneMode::Smooth) {
        try {
            textureRender_ptr->DeleteTextures();
            shapeRender_ptr->DeleteActors();
            sceneAnimation.SmoothAlgorithm(scenes[indexOfScene].scene,
                                           scenes[(indexOfScene + 1) % scenes.size()].scene);
            std::pmr::vector<LDDrift::Actors::Shape*> shapes;
            for (const auto& circle : scenes[indexOfScene].scene->circleShapes) {
                shapes.push_back(circle.circle);
            }
            for (const auto& polygon : scenes[indexOfScene].scene->polygonShapes) {
                shapes.push_back(polygon.polygon);
            }
            for (const auto& circle : scenes[(indexOfScene + 1) % scenes.size()].scene->circleShapes) {
                shapes.push_back(circle.circle);
            }
            for (const auto& polygon : scenes[(indexOfScene + 1) % scenes.size()].scene->polygonShapes) {
                shapes.push_back(polygon.polygon);
            }
            std::pmr::vector<LDDrift::Actors::Line*> lines;
            for (const auto& line : scenes[indexOfScene].scene->lines) {
                lines.push_back(line.line);
            }
            for (const auto& line : scenes[(indexOfScene + 1) % scenes.size()].scene->lines) {
                lines.push_back(line.line);
            }
            std::pmr::vector<LDDrift::Actors::Texture*> textures;
            for (const auto& texture : scenes[indexOfScene].scene->textures) {
                textures.push_back(texture.texture);
            }
            for (const auto& texture : scenes[(indexOfScene + 1) % scenes.size()].scene->textures) {
                textures.push_back(texture.texture);
            }
            LDDrift::MainRenderer::StaticDrawer(core_ptr, shapes, lines);
            LDDrift::MainRenderer::StaticDrawer(core_ptr, textures);
        } catch (const EndAnimation& e) { // append actors to renderer systems
            updateIndexOfScene();
            for (const auto& texture : scenes[indexOfScene].scene->textures) {
                textureRender_ptr->AddTexture(texture.texture, 1);
            }

            for (const auto& circle : scenes[indexOfScene].scene->circleShapes) {
                shapeRender_ptr->AddShapeToRender(circle.circle);
            }

            for (const auto& polygon : scenes[indexOfScene].scene->polygonShapes) {
                shapeRender_ptr->AddShapeToRender(polygon.polygon);
            }

            for (const auto& line : scenes[indexOfScene].scene->lines) {
                shapeRender_ptr->AddLineToRender(line.line);
            }
            currentScene = scenes[indexOfScene].scene;
            currentSceneName = scenes[indexOfScene].name;
            shapeRender_ptr->UpdateShapeData();
            shapeRender_ptr->SendDataToGPU();
            textureRender_ptr->SendToGPU();
            return true;
        } catch (const std::runtime_error& e) {
            LDDrift::Logger::ErrorLog("Engine", "Scene Manager",
                                      Log(std::string("scenes size: ") + std::to_string(scenes.size()) + "    ---    " +
                                          e.what(), LDDrift::LogType::ZeroDivideFailed));
            return false;
        } catch (const std::exception& e) {
            LDDrift::Logger::ErrorLog("Engine", "Scene Manager",
                                      Log(std::string("Error: ") + e.what(), LDDrift::LogType::Null));
            return false;
        }
    }
    return false;
}

LDDrift::Scene* LDDrift::SceneManager::GetCurrentScene() const {
    return currentScene;
}

void LDDrift::SceneManager::CreateNewScene(const std::string& name) {
    if (FindScene(name)) {
        LDDrift::Logger::WarningLog("Engine", "Scene Manager",
                                    Log(std::string("scene already exists - > ( ") + name + " )",
                                        LDDrift::LogType::FoundSceneTargetSucceeded));
        return;
    }
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

LDDrift::Scene* LDDrift::SceneManager::GetDefaultScene() {
    return &defaultScene;
}

std::size_t LDDrift::SceneManager::updateIndexOfScene() {
    try {
        if (scenes.empty()) {
            throw std::runtime_error("zero division error");
        }
        indexOfScene = (indexOfScene + 1) % scenes.size();
    } catch (const std::runtime_error& e) {
        LDDrift::Logger::WarningLog("Engine", "Scene Manager",
                                    Log(std::string(
                                            "scenes is empty | We were attempting to divide a number by 0. log: ") +
                                        e.what()
                                        , LDDrift::LogType::ZeroDivideFailed));
    } catch (const std::exception& e) {
        LDDrift::Logger::ErrorLog("Engine", "Scene Manager", Log(std::string(e.what()), LDDrift::LogType::Null));
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
    std::size_t counter = 0;
    for (auto& [sceneName, scene] : scenes) {
        if (sceneName == name) {
            indexOfScene = counter;
            textureRender_ptr->DeleteTextures();
            shapeRender_ptr->DeleteActors();
            for (const auto& circle : scene->circleShapes) {
                shapeRender_ptr->AddShapeToRender(circle.circle);
            }
            for (const auto& polygon : scene->polygonShapes) {
                shapeRender_ptr->AddShapeToRender(polygon.polygon);
            }
            for (const auto& line : scene->lines) {
                shapeRender_ptr->AddLineToRender(line.line);
            }
            for (const auto& texture : scene->textures) {
                textureRender_ptr->AddTexture(texture.texture, 1);
            }
            scene->MarkSendDataToGPU();
            scene->ReSendShapesToRender();
            currentScene = scene;
            currentSceneName = name;
            break;
        }
        ++counter;
    }
}

void LDDrift::SceneManager::SetTextureRendererPTR(LDDrift::TextureRender* texture_render_ptr) {
    textureRender_ptr = texture_render_ptr;
}

void LDDrift::SceneManager::SetShapeRenderPTR(LDDrift::ShapeRender* shape_render_ptr) {
    shapeRender_ptr = shape_render_ptr;
}

std::string LDDrift::SceneManager::GetCurrentSceneName() const {
    if (currentScene == nullptr) {
        return NULL_STRING;
    }
    if (currentScene == &defaultScene) {
        return "default";
    }
    return currentSceneName;
}

bool LDDrift::SceneManager::HasPlayingAnimation() const {
    return sceneAnimation.animation.nowPlaying;
}
