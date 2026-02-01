#pragma once

#include "../scene/action.hpp"
#include "debugmode.hpp"
#include "../actors/actors.hpp"

#define FB_COUNT 3

class Lifecycle {
    public:
        Lifecycle(DebugMode& debug) : _debug(debug) {
            initSetup();
        }
        void initSetup();
        void initDraw3d();
        void drawUi();
    private:
        DebugMode& _debug;
};