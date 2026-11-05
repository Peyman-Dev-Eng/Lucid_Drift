#ifndef LUCID_DRIFT_SCENE_ANIMATION_H
#define LUCID_DRIFT_SCENE_ANIMATION_H
#include <optional>
#include <chrono>
#include <VecCol.h>
#include <System/Scene/Scene.h>
#define ANIMATION_IN_DEFAULT_MODE 0

namespace
{
    namespace ch = std::chrono;
}

namespace LDDrift
{
    enum class ChangeSceneMode : unsigned int
    {
        Smooth = 0,
        Suddenly = 1,
        WindFromLeftToRight = 2,
        WindFromRightToLeft = 3,
        WindFromTopToBottom = 4,
        WindFromBottomToTop = 5
    };

    class SceneAnimation final
    {
    private:
        using chs = ch::steady_clock;
        using chd_double = std::chrono::duration<double>;
        using chd_float = std::chrono::duration<float>;

    public:
        struct AnimationState
        {
            bool canFree;
            bool nowPlaying; // Indicates whether the animation is currently playing
            double animationProcess; // Current animation progress (normalized between 0.0 and 1.0)
            float duration; // Total animation duration
            chs::time_point startAnimationTime; // Animation start time
            double elapsedTime; // Time elapsed since the animation started
        };

        AnimationState animation;

    private:
        void initPlayAnimation();
        void freePlayAnimation();
        [[nodiscard]] bool checkDefaultSetting() const;
        [[nodiscard]] bool CheckAnimation(const LDDrift::ChangeSceneMode& mode) const;
        static double CalculateAnimationProcess(const chs::time_point& startTime);

        const float SmoothAnimationDurationTime = 3;
        const float WindFromLeftToRightTime = 1.52f;
        const float WindFromRightToLeftTime = 1.52f;
        const float WindFromTopToBottomTime = 1.52f * 2;
        const float WindFromBottomToTopTime = 1.52f * 2;

        std::optional<ChangeSceneMode> changeSceneMode;

    public:
        SceneAnimation();
        ~SceneAnimation();
        [[nodiscard]] double GetAnimationProcess() const;
        void SmoothAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene);
        void SuddenlyAlgorithm();
        void WindFromLeftToRightAlgorithm();
        void WindFromRightToLeftAlgorithm();
        void WindFromTopToBottomAlgorithm();
        void WindFromBottomToTopAlgorithm();
    };
}

#endif
