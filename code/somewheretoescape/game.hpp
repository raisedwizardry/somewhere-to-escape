#pragma once

#include <t3d/t3d.h>
#include "physics/physics.hpp"
#include "scene/time.hpp"
#include "scene/scene.hpp"
#include "actors/actors.hpp"
#include "utility/lifecycle.hpp"

#define TARGET_FRAME_TIME_MS 33.33                                         // milliseconds for 30 FPS
#define TARGET_FRAME_TIME (TARGET_FRAME_TIME_MS * TICKS_PER_SECOND / 1000) // converting milliseconds to ticks - TICKS_PER_SECOND is defined in libdragon

class SomewhereToEscapeGame {
    public:
        SomewhereToEscapeGame(Physics& physics, Lifecycle& lifecycle, Time& time, Scene& scene, Actors& actors)
            : _physics(physics) , _lifecycle(lifecycle) , _time(time) , _scene(scene) , _actors(actors) {
        }
        void start();
    private:
        Physics& _physics;
        Lifecycle& _lifecycle;
        Time& _time;
        Scene& _scene;
        Actors& _actors;

        void updateControls();
        void setup();
        void render();
        void cleanup();
};
