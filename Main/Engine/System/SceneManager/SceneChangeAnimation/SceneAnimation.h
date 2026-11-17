#ifndef LUCID_DRIFT_SCENE_ANIMATION_H
#define LUCID_DRIFT_SCENE_ANIMATION_H
#include <optional>
#include <chrono>
#include <Actors/Shapes/Circle/CircleShape.h>
#include <Actors/Shapes/Polygon/Polygon.h>
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

    namespace Actors
    {
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
        WindFromBottomToTop = 0b1010101
    };

    class EndAnimation final
    {
    public:
        EndAnimation();
        ~EndAnimation();
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
        void initPlayAnimation(const LDDrift::Scene* cs, const LDDrift::Scene* ns);
        void freePlayAnimation(LDDrift::Scene* cs, LDDrift::Scene* ns);
        [[nodiscard]] bool checkDefaultSetting() const;
        [[nodiscard]] bool CheckAnimation(const LDDrift::ChangeSceneMode& mode) const;

    public:
        static double CalculateAnimationProcess(const chs::time_point& startTime, const double& Duration);

    private:
        const float SmoothAnimationDurationTime = 3;
        const float SuddenlyAnimationDurationTime = 0.1;

        std::optional<ChangeSceneMode> changeSceneMode;

    public:
        SceneAnimation();
        ~SceneAnimation();
        [[nodiscard]] double GetAnimationProcess() const;
        // smooth algorithm functions
        void SmoothAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene);
        // suddenly algorithm functions
        void SuddenlyAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene);
    };
}

#endif
