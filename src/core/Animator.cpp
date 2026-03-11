#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Animator.hpp"
#include <Geode/modify/GameObject.hpp>

// ID = m_uniqueID

void Anim::addTrack(int ID) {
    if (Tracks.find(ID) == Tracks.end()) {
        Tracks[ID] = Track();
    }
}

Track* Anim::getTrack(int ID) {
    if (Tracks.find(ID) != Tracks.end()) {
        return &Tracks[ID];
    }
    return nullptr;
}