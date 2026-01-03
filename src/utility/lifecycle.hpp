#pragma once

#define FB_COUNT 3

class Lifecycle {
    public:
        Lifecycle() {
            initSetup();
        }
        void initSetup();
        void initDraw3d();
        void drawUi();
};