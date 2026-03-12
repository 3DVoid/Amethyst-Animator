#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>

using namespace geode::prelude;

#include "Window.hpp"

bool AnimationWindow::init() {
    if (!CCLayer::init()) return false;

    auto winsize = CCDirector::sharedDirector()->getWinSize();

    auto windowbg = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    windowbg->setContentSize({ 150.f, 220.f });
    windowbg->setAnchorPoint({ 0.5f, 0.5f });
    windowbg->setPosition({ winsize.width, winsize.height });
    windowbg->setColor({ 18, 18, 18 });
    windowbg->setZOrder(0);
    this->addChild(windowbg);
    
    auto titleBar = CCScale9Sprite::createWithSpriteFrameName("AA_square01.png"_spr);
    titleBar->setContentSize({ 150.f, 48.f });
    titleBar->setAnchorPoint({ 0.5f, 0.5f });
    titleBar->setPosition({ 0.f, 220.f });
    titleBar->setColor({ 31, 0, 74 });
    titleBar->setZOrder(1);
    windowbg->addChild(titleBar);

    // TODO: Create buttons like File, Edit, Options and more

    return true;
}

AnimationWindow* AnimationWindow::create() {
    auto ret = new AnimationWindow();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}