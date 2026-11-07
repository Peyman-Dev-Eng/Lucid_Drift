#ifndef LUCID_DRIFT_SCENE_MANAGER_H
#define LUCID_DRIFT_SCENE_MANAGER_H
#include <System/Scene/Scene.h>
#include <System/SceneManager/SceneChangeAnimation/SceneAnimation.h>

namespace LDDrift
{

    class SceneManager final
    {
    private: // private functions
        void CreateDefaultScene();
        std::size_t updateIndexOfScene();

    private: // private variables for management
        LDDrift::Scene defaultScene;
        LDDrift::Scene* currentScene;
        std::vector<LDDrift::Scene*> scenes;
        std::size_t indexOfScene;

    private: // global variables
        LDDrift::Core* core;
        LDDrift::SceneAnimation sceneAnimation;

    public:
        SceneManager();
        ~SceneManager();
        void Initialize();
        [[nodiscard]] LDDrift::Scene* GetCurrentScene() const;
        void SetCorePTR(LDDrift::Core* core_ptr);
        void CreateNewScene();
        void ChangeScene(const LDDrift::ChangeSceneMode& mode);
        LDDrift::Scene& GetDefaultScene();
    };
}

#endif
