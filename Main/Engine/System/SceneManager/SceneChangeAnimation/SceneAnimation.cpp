/*
 * Copyright (C) 2026 Peyman
 *
 * This file is part of Lucid Drift.
 *
 * Lucid Drift is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This software is distributed without any warranty.
 *
 * See the LICENSE file for the full license text.
 * See ADDITIONAL-TERMS.md for additional terms under GPL-3.0 Section 7.
 */

#include "SceneAnimation.h"
#include <System/Scene/Scene.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <Actors/Texture/Texture.h>

LDDrift::SceneAnimation::SceneAnimation() :
    animation(false, false, 0.0, 0.0, chs::time_point::min(), 0.0) {}

LDDrift::SceneAnimation::~SceneAnimation() = default;

bool LDDrift::SceneAnimation::CheckAnimation(const LDDrift::ChangeSceneMode& mode) const {
    if (changeSceneMode.has_value() && changeSceneMode.value() == mode) {
        return true;
    }
    return false;
}

double LDDrift::SceneAnimation::CalculateAnimationProcess(const ch::time_point<ch::steady_clock>& startTime,
                                                          const double& Duration) {
    return chd_double(chs::now() - startTime).count() / Duration;
}

void LDDrift::SceneAnimation::initPlayAnimation(const LDDrift::Scene* cs, const LDDrift::Scene* ns) {
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

void LDDrift::SceneAnimation::freePlayAnimation(LDDrift::Scene* cs, LDDrift::Scene* ns) {
    animation.nowPlaying = false;
    animation.duration = 0.0f;
    animation.animationProcess = 0.0f;
    animation.startAnimationTime = chs::time_point::min();
    animation.elapsedTime = 0.0f;
    animation.canFree = false;
    changeSceneMode = std::nullopt;
    cs->freeSavedData();
    ns->freeSavedData();
}

bool LDDrift::SceneAnimation::checkDefaultSetting() const {
    return animation.nowPlaying == false && animation.duration == 0.0f && animation.animationProcess == 0.0f &&
        animation.startAnimationTime == chs::time_point::min() && animation.elapsedTime == 0.0f;
}

void LDDrift::SceneAnimation::SmoothAlgorithm(LDDrift::Scene* currentScene, LDDrift::Scene* nextScene) {
    changeSceneMode = LDDrift::ChangeSceneMode::Smooth;
    initPlayAnimation(currentScene, nextScene);
    animation.elapsedTime = chd_double(chs::now() - animation.startAnimationTime).count();
    animation.animationProcess = animation.elapsedTime / animation.duration;
    if (animation.elapsedTime >= animation.duration) {
        animation.canFree = true;
    }

    if (animation.canFree) {
        freePlayAnimation(currentScene, nextScene);
        throw EndAnimation();
    }
    currentScene->ChangeColorShapesToBlack();
    nextScene->ChangeColorShapesFromBlackToMainColor();
}

void LDDrift::SceneAnimation::SuddenlyAlgorithm(LDDrift::Scene* cs, LDDrift::Scene* ns) {
    changeSceneMode = LDDrift::ChangeSceneMode::Suddenly;
    initPlayAnimation(cs, ns);
    cs->ChangeColorShapesToBlack();
    ns->ChangeColorShapesFromBlackToMainColor();
    animation.canFree = true;
    freePlayAnimation(cs, ns);
    throw EndAnimation();
}

double LDDrift::SceneAnimation::GetAnimationProcess() const {
    if (checkDefaultSetting()) {
        return ANIMATION_IN_DEFAULT_MODE;
    }
    return animation.animationProcess;
}

LDDrift::EndAnimation::EndAnimation() = default;

LDDrift::EndAnimation::~EndAnimation() = default;
