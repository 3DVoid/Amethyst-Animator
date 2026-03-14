#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

class Trackline : public CCLayer {
    public:
        int m_ID = -1;
        bool init() override;
        static Trackline* create(int uniqueID);
        void updateTrackline();
        void setID(int uniqueID);
        std::vector<CCSprite*> keyframes;
};