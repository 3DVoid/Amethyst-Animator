#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Track.hpp"
#include "../data/Keyframe.hpp"
#include <algorithm>

void Track::addKeyframe(const KeyframeData& KF) {
    Keyframes.push_back(KF);
    Track::updateTrack();
}

void Track::updateTrack() {
    std::sort(Keyframes.begin(), Keyframes.end(), [](const KeyframeData& a, const KeyframeData& b) {
        return a.time < b.time;
    });
}

KeyframeData* Track::getKeyframe(float time) {
    auto KF = std::lower_bound(Keyframes.begin(), Keyframes.end(), time, [](const KeyframeData& kf, const float t){
        return kf.time < t;
    });

    if (KF != Keyframes.end() && KF->time == time) return &(*KF);
    return nullptr;
}

void Track::updateKeyframe(float time, std::string value, Values change) {
    auto KF = getKeyframe(time);
    if (!KF) return;

    if (value == "x") KF->X = std::get<float>(change);
    if (value == "y") KF->Y = std::get<float>(change);
    if (value == "sX") KF->sX = std::get<float>(change);
    if (value == "sY") KF->sY = std::get<float>(change);
    if (value == "rot") KF->rot = std::get<float>(change);
    if (value == "time") KF->time = std::get<float>(change);
    if (value == "easing") KF->easing = std::get<EasingType>(change);
}