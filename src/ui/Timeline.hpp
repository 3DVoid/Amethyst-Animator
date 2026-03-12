#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

class Timeline : public cocos2d::CCLayer {
    public:
        float m_time = 0.0f;
        CCNode* m_playheadGroup = nullptr;
        bool m_isDragging = false;
        CCPoint m_touchPoint;
        int m_secondDistance = 5;
        // CCSprite* m_playhead = nullptr;
        // extension::CCScale9Sprite* m_playheadLine = nullptr;
        static Timeline* create();
        bool init() override;
        static float getCurrentTime();
        bool ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
        void updateTime();
};

