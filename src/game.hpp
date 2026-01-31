#pragma once

#include "physics/physics.hpp"
#include "scene/time.hpp"
#include "scene/scene.hpp"
#include "actors/actors.hpp"
#include "menu/menu.hpp"
#include "utility/lifecycle.hpp"
#include "scene/action.hpp"

class SomewhereToEscapeGame {
    public:
        SomewhereToEscapeGame(Lifecycle& lifecycle, Physics& physics, Time& time, Scene& scene, Actors& actors, Action& action, Menu& menu)
            : _lifecycle(lifecycle) , _physics(physics) , _time(time) , _scene(scene) , _actors(actors), _action(action) , _menu(menu)  {
        }
        void start();
    private:
        Lifecycle& _lifecycle;
        Physics& _physics;
        Time& _time;
        Scene& _scene;
        Actors& _actors;
        Action& _action;
        Menu& _menu;

        void updateControls();
        void setup();
        void render();
        void cleanup();
};
