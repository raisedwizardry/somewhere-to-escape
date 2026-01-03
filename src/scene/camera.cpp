#include "camera.hpp"

#include <t3d/t3d.h>

void Camera::updateCamera(T3DViewport *viewport, T3DVec3 target) {
    camTarget = target;
    camTarget.v[2] -= 20;
    camPos.v[0] = camTarget.v[0];
    camPos.v[1] = camTarget.v[1] + 45;
    camPos.v[2] = camTarget.v[2] + 120;

    T3DVec3 camZ = {{0,1,0}};

    t3d_viewport_set_projection(viewport, T3D_DEG_TO_RAD(85.0f), 10.0f, 150.0f);
    t3d_viewport_look_at(viewport, &camPos, &camTarget, &camZ);
}
