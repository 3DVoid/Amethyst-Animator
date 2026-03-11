#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include "Track.hpp"
#include <unordered_map>


class Anim {
    public:
        Track* getTrack(int ID);
        void addTrack(int ID);
        std::unordered_map<int, Track> Tracks;
};