#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

class Trackline : public CCLayer {
    public:
        int m_ID = -1;
        int m_keyframeTouched = -1;
        CCPoint m_touchPoint;
        bool init() override;
        static Trackline* create(int uniqueID);
        void updateTrackline();
        void setID(int uniqueID);
        std::vector<CCSprite*> keyframes;
        bool ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
};