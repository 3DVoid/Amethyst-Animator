#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include "../core/Animator.hpp"
#include "../core/AnimationManager.hpp"
#include "../data/Keyframe.hpp"
#include "../ui/Window.hpp"

struct EL : Modify<EL, EditorUI> {
    AnimationWindow* m_currentWindow = nullptr;

    AnimationWindow* getWindow() {
        return m_currentWindow;
    }

    void onAABtn(CCObject*) {
        auto window = AnimationWindow::create();
        if (!window) return;
        this->addChild(window);
        m_currentWindow = window;
    }

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;
        if (!this->m_undoBtn || !this->m_undoBtn->getParent()) return false;

        log::info("Undo Button menu = {}", this->m_undoBtn->getParent()->getID());

        auto AASpr = CCSprite::createWithSpriteFrameName("AA_button01.png"_spr);
        auto AABtn = CCMenuItemSpriteExtra::create(AASpr, this, menu_selector(EL::onAABtn));
        
        auto menu = this->m_undoBtn->getParent();
        menu->addChild(AABtn);
        // Replace this with a better version bc this aint stable

        return true;
    }

    void updateObjectInfoLabel() {
        if (!m_selectedObjects) {
            EditorUI::updateObjectInfoLabel();
            return;
        }

        auto* Anim = AnimMGR::getCurrentAnimation();
        if (!Anim) {
            EditorUI::updateObjectInfoLabel();
            return;
        }

        if (!m_currentWindow || !m_currentWindow->getTimeline()) {
            EditorUI::updateObjectInfoLabel();
            return;
        }

        for (size_t i = 0; i < m_selectedObjects->count(); i++) {
            // Idk if it will for sure always return a gameobject so just doing this for safety
            auto* obj = dynamic_cast<GameObject*>(m_selectedObjects->objectAtIndex(i));
            if (!obj) {
                EditorUI::updateObjectInfoLabel();
                return;
            }

            if (auto* track = Anim->getTrack(obj->m_uniqueID)) {
                // TODO: add time and stuff and then check if something is at the time on the same track and if so then dont change.
                KeyframeData Keyframe;
                
                Keyframe.time = m_currentWindow->getTimeline()->getCurrentTime(); // TODO: add to get the current time, playhead is just gonna be everything
                if (track->getKeyframe(Keyframe.time) != nullptr) continue;
                Keyframe.X = obj->m_positionX;
                Keyframe.Y = obj->m_positionY;
                Keyframe.rot = obj->getObjectRotation();
                Keyframe.sX = obj->m_scaleX;
                Keyframe.sY = obj->m_scaleY;

                track->addKeyframe(Keyframe);
            }
        }
        EditorUI::updateObjectInfoLabel();
    }
};