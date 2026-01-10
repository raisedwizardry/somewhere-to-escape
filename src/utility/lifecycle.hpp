#pragma once

#include "../actors/animated.hpp"
#define FB_COUNT 3

class Lifecycle {
    public:
        Lifecycle(Animated& animated) : _animated(animated) {
            initSetup();
        }
        void initSetup();
        void initDraw3d();
        void drawUi();
    private:
        Animated& _animated;
};