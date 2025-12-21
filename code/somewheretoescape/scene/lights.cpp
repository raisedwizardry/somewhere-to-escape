#include <t3d/t3d.h>
#include "lights.hpp"

void Lights::setupLighting() {
    lightDirVec = {{1.0f, 1.0f, 1.0f}};
    t3d_vec3_norm(&lightDirVec);
}

void Lights::updateLighting() {
    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_directional(0, colorDir, &lightDirVec);
    t3d_light_set_count(1);
}
