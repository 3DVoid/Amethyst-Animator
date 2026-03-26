#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

#include "../data/Keyframe.hpp"

struct KeyWithSprite {
    CCSprite* keyframeSprite;
    KeyframeData* keyframe;
};

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
        void selectKeyframe(int id);
        std::unordered_map<int, KeyWithSprite*> m_selectedKeyframes;
};

