#pragma once

#include <Geode/Geode.hpp>

/* rX = rotation X
    sX = scale X
*/

struct KeyframeData {
    float time = 0.0f, X = 0.0f, Y = 0.0f, rot = 0.0f, sX = 1.0f, sY = 1.0f, alpha = 0.0f;
    EasingType easing = EasingType::None;
    cocos2d::ccColor3B color = {0, 0, 0};
    cocos2d::extension::HSV hsv = {0 ,0 ,0 };
};