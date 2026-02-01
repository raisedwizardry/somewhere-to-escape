#pragma once

#include <t3d/t3dmodel.h>
#include "../physics/physics.hpp"
#include "models/dwellerbody.hpp"
#include "models/juribody.hpp"

class Juri {
public:
    Juri(Physics& physics)
        : _physics(physics) {
    }
    JuriBody createJuriBody(T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation);
    void drawJuriBody(JuriBody *juri);
    void render(JuriBody *juri, float deltaTime);


private:
    Physics& _physics;
    T3DModel *juriModel = t3d_model_load("rom://juri.t3dm");
};
