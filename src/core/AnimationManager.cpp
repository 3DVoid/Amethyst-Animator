#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "AnimationManager.hpp"

// TODO: ADD PLAYHEAD SCRUBBING :SOB: (.update and stuff)

namespace {
    Anim* currentAnimation = nullptr;
}

Anim* AnimMGR::getCurrentAnimation() {
    return currentAnimation;
}

void AnimMGR::setCurrentAnimation(Anim* Animation) {
    currentAnimation = Animation;
}

