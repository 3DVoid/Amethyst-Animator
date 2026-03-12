#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include "../core/Animator.hpp"
#include "../core/AnimationManager.hpp"
#include "../data/Keyframe.hpp"

struct EL : Modify<EL, EditorUI> {
    void updateObjectInfoLabel() {
        if (!m_selectedObjects) {
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

            auto* Anim = AnimMGR::getCurrentAnimation();
            if (!Anim) {
                EditorUI::updateObjectInfoLabel();
                return;
            }

            if (auto* track = Anim->getTrack(obj->m_uniqueID)) {
                // TODO: add time and stuff and then check if something is at the time on the same track and if so then dont change.
                KeyframeData Keyframe;
                Keyframe.time = 0.0f; // TODO: add to get the current time, playhead is just gonna be everything
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