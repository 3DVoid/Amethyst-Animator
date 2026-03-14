#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

class Timeline : public cocos2d::CCLayer {
    public:
        float m_time = 0.0f;
        CCNode* m_playheadGroup = nullptr;
        extension::CCScale9Sprite* m_ruler;
        bool m_isDragging = false;
        CCPoint m_touchPoint;
        std::vector<CCLabelBMFont*> m_labels;
        std::string formatTime(float time);
        int m_secondDistance = 10;
        float m_scrollOffset = 0.0f;
        float m_currentTime = 0.0f;
        static Timeline* create();
        bool init() override;
        float getCurrentTime();
        bool ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
        void updateTime();
};

