#pragma once

#include <Geode/Geode.hpp>
#include "Timeline.hpp"

class AnimationWindow : public cocos2d::CCLayer {
    public:
        Timeline* m_timeline = nullptr;
        Timeline* getTimeline();
        static AnimationWindow* create();
        bool init() override;
};