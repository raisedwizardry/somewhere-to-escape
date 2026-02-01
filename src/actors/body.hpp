#pragma once

#include <t3d/t3dmodel.h>
#include "../physics/physics.hpp"
#include "models/actor.hpp"
#include "../utility/counter.hpp"

class Body {
    public:
        Body(Physics& physics, Counter& counter)
            : _physics(physics) , _counter(counter) {
        }
        ActorBody createActorBody(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation, T3DVec3 size, float mass);
        void drawActorBody(ActorBody *actor);
    private:
        Physics& _physics;
        Counter& _counter;
};