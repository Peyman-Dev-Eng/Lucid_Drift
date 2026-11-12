#include "SceneAnimation.h"
#include <System/Scene/Scene.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <System/Texture/Texture.h>

LDDrift::SceneAnimation::SceneAnimation() {
    windPosition = {0.0f, 0.0f};
}

LDDrift::SceneAnimation::~SceneAnimation() = default;

bool LDDrift::SceneAnimation::CheckAnimation(const LDDrift::ChangeSceneMode& mode) const {
    if (changeSceneMode.has_value() && changeSceneMode.value() == mode) {
        return true;
    }
    return false;
}

double LDDrift::SceneAnimation::CalculateAnimationProcess(const ch::time_point<ch::steady_clock>& startTime) {
    return chd_double(startTime - chs::now()).count();
}

void LDDrift::SceneAnimation::initPlayAnimation() {
    if (animation.nowPlaying == true) return;

    animation.nowPlaying = true;
    animation.canFree = false;
    animation.startAnimationTime = chs::now();
    if (CheckAnimation(LDDrift::ChangeSceneMode::Smooth)) {
        animation.duration = SmoothAnimationDurationTime;
    } else if (CheckAnimation(LDDrift::ChangeSceneMode::Suddenly)) {
        animation.duration = SuddenlyAnimationDurationTime; 
    }
}

void LDDrift::SceneAnimation::freePlayAnimation() {
    animation.nowPlaying = false;
    animation.duration = 0.0f;
    animation.animationProcess = 0.0f;
    animation.startAnimationTime = chs::time_point::min();
    animation.elapsedTime = 0.0f;
    animation.canFree = false;
    changeSceneMode = std::nullopt;
}

bool LDDrift::SceneAnimation::checkDefaultSetting() const {
    return animation.nowPlaying == false && animation.duration == 0.0f && animation.animationProcess == 0.0f &&
        animation.startAnimationTime == chs::time_point::min() && animation.elapsedTime == 0.0f;
}

void LDDrift::SceneAnimation::SmoothAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene) {
    changeSceneMode = LDDrift::ChangeSceneMode::Smooth;
    initPlayAnimation();
    animation.elapsedTime = chd_double(chs::now() - animation.startAnimationTime).count();
    animation.animationProcess = animation.elapsedTime / animation.duration;
    if (animation.elapsedTime >= animation.duration) {
        animation.canFree = true;
    }

    if (animation.canFree) {
        freePlayAnimation();
        return;
    }
    currentScene->ChangeColorShapesToBlack();
    nextScene->ChangeColorShapesFromBlackToMainColor();
}

void LDDrift::SceneAnimation::SuddenlyAlgorithm(LDDrift::Scene* cs, LDDrift::Scene* ns) {
    changeSceneMode = LDDrift::ChangeSceneMode::Suddenly;
    initPlayAnimation();
    cs->ChangeColorShapesToBlack();
    ns->ChangeColorShapesFromBlackToMainColor();
    animation.canFree = true;
    freePlayAnimation();
}

double LDDrift::SceneAnimation::GetAnimationProcess() const {
    if (checkDefaultSetting()) {
        return ANIMATION_IN_DEFAULT_MODE;
    }
    return animation.animationProcess;
}
