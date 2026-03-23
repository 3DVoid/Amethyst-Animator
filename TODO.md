# TODO
---

## UI
- Create buttons like File, Edit, Options and more - [Window.cpp](src/ui/Window.cpp)
- Selection/Move Mode

## Logic
- [LAST] Add Playhead Scrubbing (using .update and stuff) - [AnimationManager.cpp](src/core/AnimationManager.cpp)
- [CURRENT] Add keyframe selecting - I just added Trackline::selectKeyfame() + selectKeyframe in CCTouchBegan
- Add cycling keyframe selection
- Snapping
- Serialization
- Create commands (UI::1)
- UI::2

![](images.jpg)

## Misc
- About.md/README.md/logo.png/changelog.md/mod.json/settings
- EditorUI.cpp::36
- Keybinds

## BUILD NEEDED
- Logic
    - [BUILD] Trackline.cpp::61(updateTrackline)
    - [BUILD] Timeline.cpp::81(init[slider])
    - [BUILD] Timeline.cpp::85(init[slider])
    - [BUILD] Timeline.cpp::86(init[slider])
    - [BUILD] Timeline.cpp::253(textInputChanged)
    - [BUILD] Timeline.cpp::263(textInputChanged)
    - [BUILD] Timeline.cpp::270(onZoomMoved)


## Completed
- ~~Add timeline zooming, make ruler zoom be like every .5 seconds at at higher zoom~~
    - ~~Trackline.cpp::112(ccTouchMoved)~~
- ~~Add keyframe dragging to move keyframes~~
- ~~Handle colors with Trackline.cpp/Trackline.hpp~~
- ~~Add playhead, then in [EditorUI.cpp](src/hooks/EditorUI.cpp) add checks for if a keyframe is on the same track and same time then don't auto-create.~~
    - ~~Also add time for Keyframe with playhead~~
- ~~Add alpha, color, *transform stuff*, and hsv into Keyframe - [Keyframe.hpp](src/data/Keyframe.hpp)/[Track.cpp](src/core/Track.cpp)~~
- *Add if a keyframe is on the same time and the user adds it there, create a dupe track. (idk about this bc i might just change it so whatever is changed and the user is trying to add it automatically adds it to the keyframe on the same time instead of creating more tracks bc that will be confusing for me :P)*
- ~~Make addKeyframe in Track.cpp add it at current time (again playhead ;})~~
- ~~Turn timeline into a listview to be able to switch colors. idk tho - [Timeline.cpp](src/ui/Timeline.cpp)~~ 
- ~~Add Track**line**.cpp/hpp~~
    - ~~Also do a for loop for adding tracks into the thing. Prob gonna use List View for this but idk, I js wanna go to sleep~~
- ~~Finish UpdateTime() and ruler in Timeline.cpp (im not linking it again)~~
- ~~Add getTimeline() in [Window.hpp](src/ui/Window.hpp)/[Window.cpp](src/ui/Widnow.cpp)~~
- ~~Add refreshTracks() in [Timeline.hpp](src/ui/Timeline.hpp)/[Timeline.cpp](src/ui/Timeline.hpp)~~
- ~~Add getWindow() when doing hooks~~
- ~~Add positioning for Trackline's in [Trackline.cpp](src/ui/Trackline.cpp)/[Trackline.hpp](src/ui/Trackline.hpp)~~

# Other
- ~~I'm tired ash~~
- idk what else to put here

- Finish the mod ig, idk

- Thank You @Flurrybun on discord for helping me with updating objects (I think this works, idk I can't build yet ;P)