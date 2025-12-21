#pragma once

#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmodel.h>
#include "models/actor.hpp"
#include "body.hpp"
#include "basic.hpp"

#define TOTAL_BLOCKS    27

class Time;

class Actors {
    public:
        Actors(Physics& physics, Basic& basic, Body& body, Time& time)
            : _physics(physics) , _basic(basic) , _body(body) , _time(time) {
        }
        ~Actors();
        void updateActorsControls();
        void createActors();
        void drawActors();
        void deleteActors();
    private:
        Physics& _physics;
        Basic& _basic;
        Body& _body;
        Time& _time;

        int count = 0;
        std::vector<Actor> actors;
        std::vector<ActorBody> actorBodys;

        T3DModel *dirtBlockModel = t3d_model_load("rom:/somewheretoescape/dirtblock.t3dm");
        T3DModel *juriModel = t3d_model_load("rom:/somewheretoescape/juri.t3dm");
        T3DModel *dwellerModel = t3d_model_load("rom:/somewheretoescape/dweller.t3dm");
        T3DModel *ramModel = t3d_model_load("rom:/somewheretoescape/ram.t3dm");
        T3DModel *bunnyModel = t3d_model_load("rom:/somewheretoescape/bunny.t3dm");
        //T3DModel *squirrelModel = t3d_model_load("rom:/somewheretoescape/squirrel.t3dm");
};
