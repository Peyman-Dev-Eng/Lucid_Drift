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

#ifndef LUCID_DRIFT_SCENE_MANAGER_H
#define LUCID_DRIFT_SCENE_MANAGER_H
#include <System/Scene/Scene.h>
#include <System/SceneManager/SceneChangeAnimation/SceneAnimation.h>
#include <string>
#include <vector>

#include "WR_SettingSystem.h"

namespace LDDrift
{
    class UserProjectSetting;
    class Scene;

    class SceneManager final
    {
    private: // private functions
        void CreateDefaultScene();
        std::size_t updateIndexOfScene();
        [[nodiscard]] int GetSceneIndex(const std::string& name) const;

    private: // private variables for management
        LDDrift::Scene defaultScene;
        LDDrift::Scene* currentScene{};
        std::string currentSceneName{};
        std::size_t indexOfScene;

    private: // global variables
        LDDrift::Core* core_ptr;
        LDDrift::ShapeRender* shapeRender_ptr;
        LDDrift::TextureRender* textureRender_ptr;
        LDDrift::SceneAnimation sceneAnimation;

    public:
        struct SCENE_DATA
        {
            std::string name;
            LDDrift::Scene* scene;
        };

    private:
        friend void LDDrift::UserProjectSetting::SetSettings(const LDDrift::Core* _core_ptr);
        std::pmr::vector<SCENE_DATA> scenes;

    public:
        SceneManager();
        ~SceneManager();
        void Initialize();
        [[nodiscard]] LDDrift::Scene* GetCurrentScene() const;
        void SetCorePTR(LDDrift::Core* _core_ptr);
        void SetTextureRendererPTR(LDDrift::TextureRender* texture_render_ptr);
        void SetShapeRenderPTR(LDDrift::ShapeRender* shape_render_ptr);
        [[nodiscard]] bool FindScene(const std::string& name) const;
        void CreateNewScene(const std::string& name);
        void DeleteScene(const std::string& name);
        void ChangeScene(const std::string& name);
        void ChangeScene(const LDDrift::ChangeSceneMode& mode);
        [[nodiscard]] bool HasPlayingAnimation() const;
        LDDrift::Scene* GetDefaultScene();
        [[nodiscard]] std::string GetCurrentSceneName() const;
    };
}

#endif
