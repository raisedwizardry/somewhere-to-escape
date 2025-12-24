#pragma once

#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmodel.h>

#include "animated.hpp"
#include "models/actor.hpp"
#include "body.hpp"
#include "basic.hpp"

#define TOTAL_BLOCKS    27

class Time;

class Actors {
    public:
        Actors(Physics& physics, Animated& animated, Basic& basic, Body& body, Time& time)
            : _physics(physics) , _animated(animated), _basic(basic) , _body(body) , _time(time) {
        }
        ~Actors();
        void updateActorsControls();
        void createActors();
        void drawActors();
        void deleteActors();
    private:
        Physics& _physics;
        Animated& _animated;
        Basic& _basic;
        Body& _body;
        Time& _time;

        int count = 0;
        std::vector<Actor> actors;
        std::vector<ActorBody> actorBodys;

        T3DModel *juriModel = t3d_model_load("rom:/somewheretoescape/juri.t3dm");
        T3DModel *dwellerModel = t3d_model_load("rom:/somewheretoescape/dweller.t3dm");
        T3DModel *ramModel = t3d_model_load("rom:/somewheretoescape/ram.t3dm");
        T3DModel *bunnyModel = t3d_model_load("rom:/somewheretoescape/bunny.t3dm");
        T3DModel *squirModel = t3d_model_load("rom:/somewheretoescape/squir.t3dm");
};
