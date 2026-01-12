#pragma once

#include "../actors/animated.hpp"
#include "../scene/action.hpp"

#define FB_COUNT 3

class Lifecycle {
    public:
        Lifecycle(Animated& animated, Action& action) : _animated(animated) , _action(action) {
            initSetup();
        }
        void initSetup();
        void initDraw3d();
        void drawUi();
    private:
        Animated& _animated;
        Action& _action;
};