#pragma once

#include "../actors/animated.hpp"
#include "../scene/action.hpp"
#include "../debugmode.hpp"

#define FB_COUNT 3

class Lifecycle {
    public:
        Lifecycle(DebugMode& debug, Animated& animated, Action& action) : _debug(debug) , _animated(animated) , _action(action) {
            initSetup();
        }
        void initSetup();
        void initDraw3d();
        void drawUi();
    private:
        DebugMode& _debug;
        Animated& _animated;
        Action& _action;
};