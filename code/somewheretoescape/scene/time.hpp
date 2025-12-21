#pragma once

#include <libdragon.h>

class Time {
    public:
        void setupTime();
        void updateTime();
        float getTimeInSeconds();
        float newTime;
        float deltaTime;
        float lastTime;
        rspq_syncpoint_t syncPoint;
};
