#include "SceneAnimation.h"
#include <System/Scene/Scene.h>
#include <Actors/Shapes/MainShape/Shape.h>
#include <System/Texture/Texture.h>

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

    // save current scene
    for (const auto& circle : cs->circleShapes) {
        circleColors.push_back({{'c', circle.circle}, circle.circle->GetColorOfPoints()});
    }
    for (const auto& line : cs->lines) {
        lineColors.push_back({{'c', line.line}, line.line->GetColor()});
    }
    for (const auto& polygon : cs->polygonShapes) {
        polygonColors.push_back({{'c', polygon.polygon}, polygon.polygon->GetColorOfPoints()});
    }
    for (const auto& texture : cs->textures) {
        textureMulti.push_back({{'c', texture.texture}, texture.texture->GetColorMultiplierOfTexture()});
    }

    // save next scene
    for (const auto& circle : ns->circleShapes) {
        circleColors.push_back({{'n', circle.circle}, circle.circle->GetColorOfPoints()});
    }
    for (const auto& line : ns->lines) {
        lineColors.push_back({{'n', line.line}, line.line->GetColor()});
    }
    for (const auto& polygon : ns->polygonShapes) {
        polygonColors.push_back({{'n', polygon.polygon}, polygon.polygon->GetColorOfPoints()});
    }
    for (const auto& texture : ns->textures) {
        textureMulti.push_back({{'n', texture.texture}, texture.texture->GetColorMultiplierOfTexture()});
    }

    animation.nowPlaying = true;
    animation.canFree = false;
    animation.startAnimationTime = chs::now();
    if (CheckAnimation(LDDrift::ChangeSceneMode::Smooth)) {
        animation.duration = SmoothAnimationDurationTime;
    } else if (CheckAnimation(LDDrift::ChangeSceneMode::Suddenly)) {
        animation.duration = SuddenlyAnimationDurationTime;
    }
}

void LDDrift::SceneAnimation::freePlayAnimation(const LDDrift::Scene* cs, const LDDrift::Scene* ns) {
    animation.nowPlaying = false;
    animation.duration = 0.0f;
    animation.animationProcess = 0.0f;
    animation.startAnimationTime = chs::time_point::min();
    animation.elapsedTime = 0.0f;
    animation.canFree = false;
    changeSceneMode = std::nullopt;

    // circle
    for (const auto& [key, value] : circleColors) {
        if (key.first == 'c') {
            for (const auto& c_pointer : cs->circleShapes) {
                if (c_pointer.circle == key.second) {
                    for (std::size_t i = 0; i < value.size(); ++i) {
                        c_pointer.circle->SetPointColor(i, value[i]);
                    }
                    break;
                }
            }
        } else if (key.first == 'n') {
            for (const auto& c_pointer : ns->circleShapes) {
                if (c_pointer.circle == key.second) {
                    for (std::size_t i = 0; i < value.size(); ++i) {
                        c_pointer.circle->SetPointColor(i, value[i]);
                    }
                    break;
                }
            }
        }
    }

    // polygon
    for (const auto& [key, value] : polygonColors) {
        if (key.first == 'c') {
            for (const auto& p_pointer : cs->polygonShapes) {
                if (p_pointer.polygon == key.second) {
                    for (std::size_t i = 0; i < value.size(); ++i) {
                        p_pointer.polygon->SetPointColor(i, value[i]);
                    }
                    break;
                }
            }
        } else if (key.first == 'n') {
            for (const auto& p_pointer : ns->polygonShapes) {
                if (p_pointer.polygon == key.second) {
                    for (std::size_t i = 0; i < value.size(); ++i) {
                        p_pointer.polygon->SetPointColor(i, value[i]);
                    }
                    break;
                }
            }
        }
    }
    // line
    for (const auto& [key, value] : lineColors) {
        if (key.first == 'c') {
            for (const auto& l_pointer : cs->lines) {
                if (l_pointer.line == key.second) {
                    l_pointer.line->SetLineColor(value);
                    break;
                }
            }
        } else if (key.first == 'n') {
            for (const auto& l_pointer : ns->lines) {
                if (l_pointer.line == key.second) {
                    l_pointer.line->SetLineColor(value);
                    break;
                }
            }
        }
    }
    // texture
    for (const auto& [key, value] : textureMulti) {
        if (key.first == 'c') {
            for (const auto& t_pointer : cs->textures) {
                if (t_pointer.texture == key.second) {
                    t_pointer.texture->SetColorMultiplierForTexture(value);
                    break;
                }
            }
        } else if (key.first == 'n') {
            for (const auto& t_pointer : ns->textures) {
                if (t_pointer.texture == key.second) {
                    t_pointer.texture->SetColorMultiplierForTexture(value);
                    break;
                }
            }
        }
    }
}

bool LDDrift::SceneAnimation::checkDefaultSetting() const {
    return animation.nowPlaying == false && animation.duration == 0.0f && animation.animationProcess == 0.0f &&
        animation.startAnimationTime == chs::time_point::min() && animation.elapsedTime == 0.0f;
}

void LDDrift::SceneAnimation::SmoothAlgorithm(const LDDrift::Scene* currentScene, LDDrift::Scene* nextScene) {
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

void LDDrift::SceneAnimation::SuddenlyAlgorithm(const LDDrift::Scene* cs, LDDrift::Scene* ns) {
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
