#pragma once

#include <Geode/Geode.hpp>
#include "../data/Keyframe.hpp"
#include <variant>

using Values = std::variant<float, EasingType, cocos2d::ccColor3B, cocos2d::extension::HSV>;

class Track {
    public:
        std::vector<KeyframeData*> Keyframes;
        void addKeyframe(const KeyframeData& KF);
        void updateTrack();
        void updateKeyframe(float time, std::string value, Values change);
        KeyframeData* getKeyframe(float time);
};