#pragma once

#include <Geode/Geode.hpp>
#include "Animator.hpp"

class AnimMGR {
    public:
        static Anim* getCurrentAnimation();
        static void setCurrentAnimation(Anim* Animation);
};