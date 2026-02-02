#pragma once

#include <libdragon.h>
#include <t3d/t3dmodel.h>

#include "../physics/physics.hpp"
#include "../actors/models/actor.hpp"
#include "../actors/models/gamestate.hpp"

class Setting {
    public:
        Setting(Physics& physics)
            : _physics(physics) {
        }
        void createSetting();
        void drawMap(GameState gameState);
    private:
        Physics& _physics;
        T3DModel *greenModel = t3d_model_load("rom:/map.t3dm");
        T3DModel *forestModel = t3d_model_load("rom:/forest.t3dm");
        T3DModel *juriWorldModel = t3d_model_load("rom:/juri-world.t3dm");
        Actor greenMap = {
            .scale = (T3DVec3){{0.05f, 0.05f, 0.05f}},
            .position = (T3DVec3){{0.0f, 0.0f, -100.0f}},
            .rotation = (T3DVec3){{0.0f, 0.0f, 0.0f}},
            .modelMat =(T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP))
        };
        Actor forestMap = {
            .scale = (T3DVec3){{0.05f, 0.05f, 0.05f}},
            .position = (T3DVec3){{0.0f, 0.0f, 0.0f}},
            .rotation = (T3DVec3){{0.0f, 0.0f, 0.0f}},
            .modelMat =(T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP))
        };
        Actor juriWorldMap = {
            .scale = (T3DVec3){{0.05f, 0.05f, 0.05f}},
            .position = (T3DVec3){{0.0f, 0.0f, 100.0f}},
            .rotation = (T3DVec3){{0.0f, 0.0f, 0.0f}},
            .modelMat =(T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP))
        };
};
