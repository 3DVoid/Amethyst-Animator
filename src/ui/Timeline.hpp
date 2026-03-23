#pragma once

#include <Geode/Geode.hpp>
#include "../core/Track.hpp"
#include "Trackline.hpp"
#include <string>
#include <Geode/binding/TextInputDelegate.hpp>
#include <Geode/binding/Slider.hpp>

using namespace cocos2d;

struct TrackData {
    bool pendingName = true;
    Track* track;
    Trackline* trackline;
    std::string name;
};

// LV = ListView

class Timeline : public cocos2d::CCLayer {
    public:
        float m_time = 0.0f;
        cocos2d::CCArray* m_trackItems = cocos2d::CCArray::create();
        geode::ListView* m_trackLV = nullptr;
        cocos2d::CCArray* m_trackNames = cocos2d::CCArray::create();
        geode::ListView* m_nameLV = nullptr;
        CCNode* m_playheadGroup = nullptr;
        extension::CCScale9Sprite* m_ruler;
        bool m_isDragging = false;
        CCPoint m_touchPoint;
        std::vector<CCLabelBMFont*> m_labels;
        std::string formatFloat(float num, int precision);
        int m_secondDistance = 10;
        float m_scrollOffset = 0.0f;
        float m_currentTime = 0.0f;
        float m_interval = 1.f;
        float m_zoom = 50.f;
        Slider* m_slider;
        static Timeline* create();
        bool init() override;
        float getCurrentTime();
        bool ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
        void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
        void onZoomMoved(CCObject* sender);
        void updateTime();
        void refreshTracks();
        std::unordered_map<int, TrackData> Tracks;
};

class TD : public TextInputDelegate {
    public:
        void textInputClosed(CCTextInputNode* node) override;
        std::string last_string = "0%";
};