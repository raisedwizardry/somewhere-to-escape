#pragma once

#include <t3d/t3dmodel.h>
#include "../physics/physics.hpp"
#include "models/dwellerbody.hpp"

class Dweller {
public:
    Dweller(Physics& physics)
        : _physics(physics) {
    }
    DwellerBody createDwellerBody(T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation, T3DVec3 size, float mass);
    void drawDwellerBody(DwellerBody *dweller);
    void render(DwellerBody *dweller, float deltaTime);


    DwellerBody dweller1;
    DwellerBody dweller2;
    DwellerBody dweller3;
    DwellerBody dweller4;
private:
    Physics& _physics;
    T3DModel *dwellerModel = t3d_model_load("rom:/dweller.t3dm");
};
