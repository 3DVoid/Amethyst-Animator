#pragma once

#include <Geode/Geode.hpp>

/* rX = rotation X
    sX = scale X
*/

struct KeyframeData {
    float time = 0.0f, X = 0.0f, Y = 0.0f, rot = 0.0f, sX = 1.0f, sY = 1.0f;
    EasingType easing = EasingType::None;
};