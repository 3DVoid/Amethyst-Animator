#pragma once

#include <Geode/Geode.hpp>

class AnimationWindow : public cocos2d::CCLayer {
    public:
        static AnimationWindow* create();
        bool init() override;
};