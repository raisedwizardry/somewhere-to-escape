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
        //T3DModel *mapModel = t3d_model_load("rom:/somewheretoescape/map.t3dm");
};
