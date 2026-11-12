#ifndef LUCID_DRIFT_SCENE_MANAGER_H
#define LUCID_DRIFT_SCENE_MANAGER_H
#include <System/Scene/Scene.h>
#include <System/SceneManager/SceneChangeAnimation/SceneAnimation.h>
#include <string>
#include <vector>

namespace LDDrift
{
    class Scene;

    class SceneManager final
    {
    private: // private functions
        void CreateDefaultScene();
        std::size_t updateIndexOfScene();
        int GetSceneIndex(const std::string& name);

    private: // private variables for management
        LDDrift::Scene defaultScene;
        LDDrift::Scene* currentScene;
        std::size_t indexOfScene;

    private: // global variables
        LDDrift::Core* core;
        LDDrift::SceneAnimation sceneAnimation;

    public:
        struct SCENE_DATA {
            std::string name;
            LDDrift::Scene* scene;
        };

        std::vector<SCENE_DATA> scenes;

    public:
        SceneManager();
        ~SceneManager();
        void Initialize();
        [[nodiscard]] LDDrift::Scene* GetCurrentScene() const;
        void SetCorePTR(LDDrift::Core* core_ptr);
        bool FindScene(const std::string& name);
        void CreateNewScene(const std::string& name);
        void DeleteScene(const std::string& name);
        void ChangeScene(const std::string& name);
        void ChangeScene(const LDDrift::ChangeSceneMode& mode);
        LDDrift::Scene& GetDefaultScene();
    };
}

#endif
