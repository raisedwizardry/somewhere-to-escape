#include "time.hpp"
#include <libdragon.h>

void Time::setupTime() {
    lastTime = getTimeInSeconds() - (1.0f / 60.0f);
    syncPoint = 0;
}

void Time::updateTime() {
    newTime = getTimeInSeconds();
    deltaTime = newTime - lastTime;
    lastTime = newTime;

    if (syncPoint) {
        rspq_syncpoint_wait(syncPoint);
    }
}

float Time::getTimeInSeconds() {
    return (float)((double)get_ticks_us() / 1000000.0);
}
