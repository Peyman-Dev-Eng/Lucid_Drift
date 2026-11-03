#ifndef LUCID_DRIFT_SCENE_MANAGER_H
#define LUCID_DRIFT_SCENE_MANAGER_H
#include <System/Scene/Scene.h>

namespace LDDrift
{
    enum ChangeSceneMode
    {
        Smooth,
        Suddenly,
        WindFromLeftToRight,
        WindFromRightToLeft,
        WindFromTopToBottom,
        WindFromBottomToTop
    };

    class SceneManager
    {
    private: // scene changing algorithm (functions)
        void SmoothChangeScene();
        void SuddenlyChangeScene();
        void WindFromLeftToRightChangeScene();
        void WindFromRightToLeftChangeScene();
        void WindFromTopToBottomChangeScene();
        void WindFromBottomToTopChangeScene();

    private:
        std::vector<LDDrift::Scene*> scenes;

    public:
        SceneManager();
        ~SceneManager();
        void CreateNewScene();
        void ChangeScene();
    };
}

#endif
