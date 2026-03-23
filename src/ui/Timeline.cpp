#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>
#include <iomanip>
#include <sstream>
#include <regex>
#include <cmath>
#include <Geode/ui/ListView.hpp>
#include <Geode/ui/TextInput.hpp>
#include <Geode/binding/Slider.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;
using namespace cocos2d;

#include "Timeline.hpp"
#include "../core/AnimationManager.hpp"
#include "../core/Animator.hpp"
#include "../hooks/EditorUI.cpp"

bool Timeline::init() {
    if (!Timeline::init()) return false;
    // I might have to add checks for my sprites
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);

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
    playhead->setPosition({ 0.f, 86.f }); // might have to change this to 172
    playhead->setZOrder(3);
    m_playheadGroup->addChild(playhead);

    auto playheadLine = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    playheadLine->setContentSize({ 2.f, 172.f });
    playheadLine->setAnchorPoint({ 0.5f, 0.5f });
    playheadLine->setPosition({ 0.f, 0.f });
    playheadLine->setZOrder(3);
    m_playheadGroup->addChild(playheadLine);
    m_playheadGroup->setPosition( -50.f, 0.f );
    timelineBg->addChild(m_playheadGroup);

    m_ruler = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    m_ruler->setContentSize({ 100.f, 10.f });
    m_ruler->setAnchorPoint({ 0.f, 0.f });
    m_ruler->setPosition({ 100.f, 172.f }); // might have to change to 50.f, 172.f / 2.f
    m_ruler->setColor({ 93, 60, 109 });
    m_ruler->setOpacity(200); // adjust this maybe
    m_ruler->setZOrder(2);
    timelineBg->addChild(m_ruler);

    if (!m_trackItems) return false;
    m_trackLV = ListView::create(m_trackItems, 27, 100, 162);
    if (!m_trackLV) return false;
    m_trackLV->setPrimaryCellColor({ 23, 23, 23 });
    m_trackLV->setSecondaryCellColor({ 38, 0, 59 });
    m_trackLV->setAnchorPoint({ 1.f, 0.f });
    timelineBg->addChildAtPosition(m_trackLV, Anchor::BottomRight);
    
    if (!m_trackNames) return false;
    m_nameLV = ListView::create(m_trackNames, 27, 50, 162);
    if (!m_nameLV) return false;
    m_nameLV->setPrimaryCellColor({ 33, 33, 33 });
    m_nameLV->setSecondaryCellColor({ 48, 10, 69 });
    m_nameLV->setAnchorPoint({ 0.f, 0.f });
    timelineBg->addChildAtPosition(m_nameLV, Anchor::BottomLeft);

    m_slider = Slider::create(this, menu_selector(Timeline::onZoomMoved), "SliderBar01.png"_spr, "slidergroove2.png", "SliderThumb01.png"_spr, "SliderThumb01.png"_spr, 1.f); // change maybe
    if (!m_slider) return false;
    m_slider->setScale(35.f / m_slider->m_width);
    m_slider->setAnchorPoint({ 1.f, 0.f });
    m_slider->setValue(m_zoom / 100); // idk if its from 0-1
    timelineBg->addChildAtPosition(m_slider, Anchor::BottomRight, {10.f, 10.f}); // might have to change

    auto zoom = CCTextInputNode::create(35.f, 35.f, "0%", "cour.ttf");
    if (!zoom) return false;
    zoom->setString(std::to_string(m_zoom) + "%");
    auto textDelegate = new TD();
    if (!textDelegate) return false;
    textDelegate->last_string = zoom->getString();
    zoom->setDelegate(textDelegate);

    m_secondDistance = m_zoom / 5;
    if (5 >= m_secondDistance || m_secondDistance >= 15) {
        auto result = numFromString<float>(formatFloat(5.f / m_secondDistance, 2));
        if (!result) {
            m_interval = round((5.f / m_secondDistance) * 2.f) / 2.f;
        } else {
            m_interval = result.unwrap();
        }
    }
    m_interval = round((5.f / m_secondDistance) * 2.f) / 2.f;

    refreshTracks();

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

bool Timeline::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (!pTouch) return false;
    m_touchPoint = convertTouchToNodeSpace(pTouch);
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
    if (!pTouch) return;
    auto movePoint = convertTouchToNodeSpace(pTouch);

    if (fabs(movePoint.x - m_touchPoint.x) > 10.f ) {
        m_isDragging = true;
    }
    
    if (m_isDragging) {
        if (movePoint.x >= 50) {
            m_scrollOffset = movePoint.x - m_touchPoint.x;
        }
        m_playheadGroup->setPositionX(movePoint.x);
        updateTime();
    }
}

void Timeline::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    // Add keyframe selecting and stuff. Basically just touch handling | Nope bc thats gonna be in Trackline.cpp :)
}

std::string Timeline::formatFloat(float num, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << num;
    return ss.str();
}

void Timeline::updateTime() {
    if (!m_ruler || !m_playheadGroup) return;
    m_currentTime = (m_playheadGroup->getPositionX() + m_scrollOffset) / m_secondDistance;
    
    float startTime = floor(m_scrollOffset / (1 * m_secondDistance)) * 1; // 1 is a placeholder for when I add zooming and add .5 and stuff, check TODO.md::14
    float endTime = ceil((m_scrollOffset + 100) / (1 * m_secondDistance)); // ^, 100 is ruler width

    int index = 0;
    for (float time = startTime; time <= endTime; time++) { // ^^^^ (103)
        if (index < m_labels.size()) {
            m_labels[index]->setVisible(true);
        } else {
            auto label = CCLabelBMFont::create(formatFloat(time, 2).c_str(), "cour.ttf");
            label->setPositionX(time * m_secondDistance);
            m_ruler->addChild(label);
            m_labels.push_back(label);
        }
    }

    for (int i = index; i < m_labels.size(); i++) {
        m_labels[i]->setVisible(false);
    }

    refreshTracks();
}

float Timeline::getCurrentTime() {
    return m_currentTime;
}

void Timeline::refreshTracks() {
    auto anim = AnimMGR::getCurrentAnimation();
    if (!anim || !m_trackLV || !m_trackItems || !m_nameLV || !m_trackNames) return;
    
    auto index = 1;
    for (auto& track1 : anim->Tracks) {
        if (Tracks.find(track1.first) != Tracks.end()) {
            auto it = Tracks.find(track1.first);
            auto track = it->second;
            
            if (!track.trackline) {
                auto trackline = Trackline::create(it->first);
                track.trackline = trackline;
                m_trackItems->addObject(trackline);
                m_trackLV->reloadAll();
            } else {
                track.trackline->updateTrackline();
            }

            if (track.pendingName) {
                auto label = CCTextInputNode::create(40, 27, "Enter text here...", "cour.ttf");
                if (!label) continue;
                label->setMaxLabelLength(20);
                label->setLabelNormalColor({ 255, 255, 255 });
                label->setString("Object " + std::to_string(index));
                label->refreshLabel();
                track.name = label->getString();
                track.pendingName = false;
                m_trackNames->addObject(label);
                m_nameLV->reloadAll();
            }
            index++;
        }
    }
}

void TD::textInputClosed(CCTextInputNode* node) {
    if (!node) return;
    auto text = node->getString();
    auto filter = std::regex_replace(text, std::regex("[^0-9]+"), "");

    auto EditorUI = EL::get();
    if (!EditorUI) {
        node->setString(last_string);
        return;
    }
    auto EL = dynamic_cast<struct EL*>(EditorUI);
    if (!EL) {
        node->setString(last_string);
        return;
    };
    auto window = EL->getWindow();
    if (!window) {
        node->setString(last_string);
        return;
    };
    auto timeline = window->getTimeline();
    if (!timeline || !timeline->m_slider || !timeline->m_zoom) {
        node->setString(last_string);
        return;
    };

    if (filter.empty()) {
        node->setString(last_string);
        auto LSFilter = std::regex_replace(last_string, std::regex("[^0-9]+"), "");
        if (LSFilter.empty()) return;
        auto result = numFromString<float>(LSFilter);
        if (!result) return;
        timeline->m_zoom = result.unwrap();
        timeline->m_slider->setValue(result.unwrap() / 100); // idk if its from 0-1
        timeline->m_secondDistance = timeline->m_zoom / 5;
        if (5 >= timeline->m_secondDistance || timeline->m_secondDistance >= 15) {
            auto result = numFromString<float>(timeline->formatFloat(5.f / timeline->m_secondDistance, 2));
            if (!result) {
                timeline->m_interval = round((5.f / timeline->m_secondDistance) * 2.f) / 2.f;
                return;
            }
            timeline->m_interval = result.unwrap();
        }
        timeline->m_interval = round((5.f / timeline->m_secondDistance) * 2.f) / 2.f;
        timeline->refreshTracks();
    } else {
        auto result = numFromString<float>(filter);
        if (!result) {
            node->setString(last_string);
            return;
        }
        node->setString(filter + "%");

        timeline->m_zoom = result.unwrap();
        timeline->m_slider->setValue(result.unwrap() / 100); // idk if its from 0-1
        timeline->m_secondDistance = timeline->m_zoom / 5;
        if (5 >= timeline->m_secondDistance || timeline->m_secondDistance >= 15) {
            auto result = numFromString<float>(timeline->formatFloat(5.f / timeline->m_secondDistance, 2));
            if (!result) {
                timeline->m_interval = round((5.f / timeline->m_secondDistance) * 2.f) / 2.f;
                return;
            }
            timeline->m_interval = result.unwrap();
        }
        timeline->m_interval = round((5.f / timeline->m_secondDistance) * 2.f) / 2.f;
        timeline->refreshTracks();
    }
}

void Timeline::onZoomMoved(CCObject* sender) {
    auto slider = dynamic_cast<Slider*>(sender);
    if (!slider) return;
    m_zoom = slider->getValue() * 100; // idk if its from 0-1
    m_secondDistance = m_zoom / 5;
    if (5 >= m_secondDistance || m_secondDistance >= 15) {
        auto result = numFromString<float>(formatFloat(5.f / m_secondDistance, 2));
        if (!result) {
            m_interval = round((5.f / m_secondDistance) * 2.f) / 2.f;
            return;
        }
        m_interval = result.unwrap();
    }
    m_interval = round((5.f / m_secondDistance) * 2.f) / 2.f;
    refreshTracks();
}