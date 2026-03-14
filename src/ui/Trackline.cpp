#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Trackline.hpp"
#include "../core/AnimationManager.hpp"
#include "../core/Animator.hpp"
#include "../hooks/EditorUI.cpp"

// PLC = Placeholder

Trackline* Trackline::create(int uniqueID) {
    auto ret = new Trackline();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Trackline::init() {
    if (!Trackline::init()) return false;

    auto PLCLine = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    if (!PLCLine) return false;
    PLCLine->setContentSize({ 100, 25 });
    PLCLine->setOpacity(0);

    return true;
}

void Trackline::setID(int uniqueID) {
    m_ID = uniqueID;
}

void Trackline::updateTrackline() {
    auto Anim = AnimMGR::getCurrentAnimation();
    if (!Anim) return;

    auto track = Anim->getTrack(m_ID);
    if (!track) return;

    auto index = 0;
    
    auto EditorUI = EL::get();
    if (!EditorUI) return;
    auto EL = dynamic_cast<struct EL*>(EditorUI);
    if (!EL) return;
    auto window = EL->getWindow();
    if (!window) return;
    auto timeline = window->getTimeline();
    if (!timeline) return;

    auto start = timeline->m_scrollOffset / timeline->m_secondDistance;
    auto end = (timeline->m_scrollOffset + 100) / timeline->m_secondDistance; // 100 is timeline width

    keyframes.clear();
    for (int i = 0; i < track->Keyframes.size(); i++) {
        auto keyframeSprite = CCSprite::createWithSpriteFrameName("Keyframe.png"_spr);
        keyframeSprite->setContentSize({ 25.f, 25.f });
        keyframeSprite->setTag(i);
        keyframes.push_back(keyframeSprite);
        auto& keyframe = track->Keyframes[i];
        if (keyframe.time >= start && keyframe.time <= end) {
            keyframeSprite->setPositionX((keyframe.time * timeline->m_secondDistance) - timeline->m_scrollOffset);
            keyframeSprite->setVisible(true);
            index++;
        } else {
            keyframeSprite->setVisible(false);
        }
    }
}