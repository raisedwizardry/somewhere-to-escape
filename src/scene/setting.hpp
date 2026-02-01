#pragma once

#include <libdragon.h>
#include <t3d/t3dmodel.h>

#include "../physics/physics.hpp"

class Setting {
    public:
        Setting(Physics& physics)
            : _physics(physics) {
        }
        void createSetting();
        void drawMap();
    private:
        Physics& _physics;
        rspq_block_t *dplMap;
        T3DMat4FP* mapMatFP;
        T3DModel *mapModel = t3d_model_load("rom:/map.t3dm");
        float planeRotationX = 0.0f;
        float planeRotationZ = 0.0f;
        float planeRotation = 0.0f;
        T3DVec3 rotAxisX = {{1.0f, 0.0f, 0.0f}};
        T3DVec3 rotAxisZ = {{0.0f, 0.0f, 1.0f}};
        T3DVec3 rotAxis = {{0.0f, 0.0f, 0.0f}};
        T3DMat4 modelMat;
        rspq_block_t *dplDraw;
        T3DMat4FP *modelMatFP;
        T3DVertPacked *vertices;
};
