#pragma once

#include "physics/physics.hpp"
#include "scene/time.hpp"
#include "scene/scene.hpp"
#include "actors/actors.hpp"
#include "utility/lifecycle.hpp"
#include "scene/action.hpp"

class SomewhereToEscapeGame {
    public:
        SomewhereToEscapeGame(Physics& physics, Lifecycle& lifecycle, Time& time, Scene& scene, Actors& actors, Action& action)
            : _physics(physics) , _lifecycle(lifecycle) , _time(time) , _scene(scene) , _actors(actors), _action(action) {
        }
        void start();
    private:
        Physics& _physics;
        Lifecycle& _lifecycle;
        Time& _time;
        Scene& _scene;
        Actors& _actors;
        Action& _action;
        void updateControls();
        void setup();
        void render();
        void cleanup();
};
