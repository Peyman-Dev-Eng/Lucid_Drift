#ifndef LUCID_DRIFT_SCENE_ANIMATION_H
#define LUCID_DRIFT_SCENE_ANIMATION_H
#include <optional>
#include <chrono>
#include <VecCol.h>
#include <VecPos.h>
#define ANIMATION_IN_DEFAULT_MODE 0

namespace
{
    namespace ch = std::chrono;
}

namespace LDDrift
{
    class Texture;
    namespace Actors {
        class Shape;
        class Line;
    }

    class Scene;
    enum class ChangeSceneMode : unsigned int
    {
        Smooth = 0b10,
        Suddenly = 0b101,
        WindFromLeftToRight = 0b1010,
        WindFromRightToLeft = 0b10101,
        WindFromTopToBottom = 0b101010,
        WindFromBottomToTop = 0b1010101,
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

        LDDrift::VecPos2D windPosition;

        AnimationState animation;

        struct WindAnimation
        {
            int xPos;
            int yPos;
        };

        WindAnimation windAnimation;

    private:
        void initPlayAnimation();
        void freePlayAnimation();
        [[nodiscard]] bool checkDefaultSetting() const;
        [[nodiscard]] bool CheckAnimation(const LDDrift::ChangeSceneMode& mode) const;
        static double CalculateAnimationProcess(const chs::time_point& startTime);

        const float SmoothAnimationDurationTime = 3;
        const float SuddenlyAnimationDurationTime = 0.1;

        std::optional<ChangeSceneMode> changeSceneMode;

    public:
        SceneAnimation();
        ~SceneAnimation();
        [[nodiscard]] double GetAnimationProcess() const;
        // smooth algorithm functions
        void SmoothAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene);
        // suddenly algoritm functions
        void SuddenlyAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene);
  };
}

#endif
