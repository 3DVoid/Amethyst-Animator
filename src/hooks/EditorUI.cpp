#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include "../core/Animator.hpp"
#include "../core/AnimationManager.hpp"
#include "../data/Keyframe.hpp"

struct EL : Modify<EL, EditorUI> {
    void updateObjectInfoLabel() {
        if (auto track = AnimMGR::getCurrentAnimation()->getTrack(m_selectedObject->m_uniqueID)) {
            // TODO: add time and stuff and then check if something is at the time on the same track and if so then dont change.
            KeyframeData Keyframe;
            Keyframe.time = 0.0f; // TODO: add to get the current time, playhead is just gonna be everything
            Keyframe.X = m_selectedObject->m_positionX;
            Keyframe.Y = m_selectedObject->m_positionY;
            Keyframe.rot = m_selectedObject->getObjectRotation();
            Keyframe.sX = m_selectedObject->m_scaleX;
            Keyframe.sY = m_selectedObject->m_scaleY;

            track->addKeyframe(Keyframe);
        }
        EditorUI::updateObjectInfoLabel();
    }
};