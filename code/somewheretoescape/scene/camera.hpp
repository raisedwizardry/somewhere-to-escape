#pragma once

#include <t3d/t3d.h>

class Camera {
    public:
        void updateCamera(T3DViewport *viewport, T3DVec3 target = {{0,0.15f,0}});
        T3DViewport viewport;
    private:
        T3DVec3 camPos = {{0, 45.0f, 80.0f}};
        T3DVec3 camTarget = {{0, 0,-10}};
};
