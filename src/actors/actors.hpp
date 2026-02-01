#pragma once

#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmodel.h>

#include "animated.hpp"
#include "models/actor.hpp"
#include "body.hpp"
#include "basic.hpp"
#include "../utility/debugmode.hpp"


#define TOTAL_BLOCKS    27

class Camera;
class Time;

class Actors {
    public:
        Actors(Physics& physics, Animated& animated, Basic& basic, Body& body, Time& time, Camera& camera, DebugMode& debug)
            : _physics(physics) , _animated(animated), _basic(basic) , _body(body) , _time(time) , _camera(camera) , _debug(debug) {
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
        Camera& _camera;
        DebugMode& _debug;

        int count = 0;
        std::vector<Actor> actors;
        std::vector<ActorBody> actorBodys;

        T3DModel *juriModel = t3d_model_load("rom:/juri.t3dm");
        T3DModel *dwellerModel = t3d_model_load("rom:/dweller.t3dm");

        T3DModel *ramModel = t3d_model_load("rom:/ram.t3dm");
        T3DModel *nModel = t3d_model_load("rom:/n.t3dm");
        T3DModel *caveModel = t3d_model_load("rom:/cave.t3dm");
        T3DModel *markerModel = t3d_model_load("rom:/marker.t3dm");
        T3DModel *bunnyModel = t3d_model_load("rom:/bunny.t3dm");
        T3DModel *squirModel = t3d_model_load("rom:/squir.t3dm");
};
