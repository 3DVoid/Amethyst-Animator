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
        ret->setID(uniqueID);
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void Trackline::setID(int uniqueID) {
    m_ID = uniqueID;
}

bool Trackline::init() {
    if (!Trackline::init()) return false;

    auto PLCLine = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    if (!PLCLine) return false;
    PLCLine->setContentSize({ 100, 27 });
    PLCLine->setOpacity(0);

    updateTrackline();

    return true;
}

void Trackline::updateTrackline() {
    auto Anim = AnimMGR::getCurrentAnimation();
    if (!Anim) return;

    auto track = Anim->getTrack(m_ID);
    if (!track) return;

    // auto index = 0;
    
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

    for (auto ks : keyframes) { // prob change if always parent
        if (ks->getParent()) {
            ks->removeFromParent();
        } else {
            delete ks;
        }
    }
    keyframes.clear();
    for (int i = 0; i < track->Keyframes.size(); i++) {
        auto keyframeSprite = CCSprite::createWithSpriteFrameName("Keyframe.png"_spr);
        keyframeSprite->setContentSize({ 27.f, 27.f });
        keyframeSprite->setTag(i);
        this->addChild(keyframeSprite);
        keyframes.push_back(keyframeSprite);
        auto& keyframe = track->Keyframes[i];
        if (keyframe.time >= start && keyframe.time <= end) {
            keyframeSprite->setPositionX((keyframe.time * timeline->m_secondDistance) - timeline->m_scrollOffset);
            keyframeSprite->setVisible(true);
            
            // index++;
        } else {
            keyframeSprite->setVisible(false);
        }
    }
}

bool Trackline::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (!pTouch) return false;
    m_touchPoint = pTouch->getLocation();

    auto anim = AnimMGR::getCurrentAnimation();
    if (!anim) return false;

    auto track = anim->getTrack(m_ID);
    if (!track) return false;

    auto touch = this->convertTouchToNodeSpace(pTouch);
    for (auto& keyframe : keyframes) {
        if (keyframe->boundingBox().containsPoint(touch)) {
            m_keyframeTouched = keyframe->getTag();
            return true;
        }
    }

    return false;
}

void Trackline::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    if (!pTouch) return;
    auto movePoint = convertTouchToNodeSpace(pTouch);

    auto anim = AnimMGR::getCurrentAnimation();
    if (!anim) return;

    auto track = anim->getTrack(m_ID);

    auto EditorUI = EL::get();
    if (!EditorUI) return;
    auto EL = dynamic_cast<struct EL*>(EditorUI);
    if (!EL) return;
    auto window = EL->getWindow();
    if (!window) return;
    auto timeline = window->getTimeline();
    if (!timeline) return;

    if (fabs(movePoint.x - m_touchPoint.x) > timeline->m_secondDistance / 1.f) { // 1 is a placeholder for my interval
        auto& keyframe = track->Keyframes[m_keyframeTouched];
        auto keyframeSprite = keyframes[m_keyframeTouched];
        if (!keyframeSprite) return;
        keyframeSprite->setPositionX(round(movePoint.x / (timeline->m_secondDistance / 1.f)) * (timeline->m_secondDistance / 1.f) - timeline->m_scrollOffset); // ^^
        keyframe.time = round((keyframeSprite->getPositionX() + timeline->m_scrollOffset) / 1.f); // ^
    }
}