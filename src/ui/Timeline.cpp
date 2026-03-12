#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>

using namespace geode::prelude;
using namespace cocos2d;

#include "Timeline.hpp"
#include "../core/AnimationManager.hpp"

bool Timeline::init() {
    if (!Timeline::init()) return false;
    // I might have to add checks for my sprites
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    // TODO?: Turn timeline into a listview to be able to switch colors. idk tho
    auto timelineBg = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    timelineBg->setContentSize({ 100.f, 162.f });
    timelineBg->setAnchorPoint({ 0.5f, 0.5f });
    // timelineBg->setPosition({ 0.f, 0.f });
    timelineBg->setColor({ 33, 24, 48 });
    timelineBg->setZOrder(1);
    this->addChildAtPosition(timelineBg, Anchor::Right);

    auto seperator = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    seperator->setContentSize({ 2.f, 162.f });
    seperator->setAnchorPoint({ 0.5f, 0.5f });
    seperator->setPosition({ -15.f, 0.f }); // might have to do -25
    seperator->setColor({ 0, 0, 0 });
    seperator->setZOrder(2);
    timelineBg->addChild(seperator);

    auto playhead = CCSprite::createWithSpriteFrameName("Playhead.png"_spr);
    playhead->setAnchorPoint({  0.5f, 1.f });
    playhead->setPosition({ 0.f, 172.f }); // might have to change this to 172 / 2
    playhead->setZOrder(3);
    m_playheadGroup->addChild(playhead);

    auto playheadLine = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    playheadLine->setContentSize({ 2.f, 172.f });
    playheadLine->setAnchorPoint({ 0.5f, 0.5f });
    playheadLine->setPosition({ 0.f, 0.f });
    playheadLine->setZOrder(3);
    m_playheadGroup->addChild(playheadLine);
    m_playheadGroup->setPosition( 100.f, 0.f );
    timelineBg->addChild(m_playheadGroup);

    auto ruler = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    ruler->setContentSize({ 100.f, 10.f });
    ruler->setAnchorPoint({ 1.f, 1.f });
    ruler->setPosition({ 100.f, 172.f }); // might have to change to 50.f, 172.f / 2.f
    ruler->setColor({ 93, 60, 109 });
    ruler->setZOrder(2);
    timelineBg->addChild(ruler);

    return true;
}

Timeline* Timeline::create() {
    auto ret = new Timeline();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Timeline::ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    m_touchPoint = pTouch->getLocation();
    m_isDragging = false;
    if (!m_playheadGroup) return false;
    auto pGPos = m_playheadGroup->getPosition();
    auto pGSize = m_playheadGroup->getContentSize();
    CCRect PHhitbox(pGPos.x - pGSize.width / 2, pGPos.y - pGSize.height / 2, pGSize.width, pGSize.height);

    if (PHhitbox.containsPoint(pTouch->getLocation())) {
        return true;
    }

    return false;
}

void Timeline::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    auto currentPoint = pTouch->getLocation();

    if (fabs(currentPoint.x - m_touchPoint.x) > 10.f ) {
        m_isDragging = true;
    }
    
    if (m_isDragging) {
        m_playheadGroup->setPositionX(currentPoint.x);
    }
}

void Timeline::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    // Add keyframe selecting and stuff. Basically just touch handling
}

void Timeline::updateTime() {

}