#pragma once

#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "models/actor.hpp"
#include "../utility/counter.hpp"

class Basic {
    public:
        Basic(Counter& counter)
            : _counter(counter) {
        }
        Actor createActor(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition);
        void drawActor(Actor *actor, T3DVec3 position, T3DVec3 rotation);
    private:
        Counter& _counter;
};
