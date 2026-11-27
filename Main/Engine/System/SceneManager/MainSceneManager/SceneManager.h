// Copyright 2026 Peyman
// https://github.com/Peyman-Dev-Eng/Lucid_Drift
//
// This file is part of Lucid Drift.
// Licensed under GNU GPL v3.0.
// See LICENSE and ADDITIONAL-TERMS.md.

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
