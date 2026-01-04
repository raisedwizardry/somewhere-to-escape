#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>
#include "../actors/models/complex.hpp"

namespace bodyForce {

    inline void applyForce(ComplexBody* body, T3DVec3 direction, float amount) {
        body->rigidBody->applyForce(btVector3(direction.x, direction.y, direction.z), btVector3(amount, amount, amount));
    }

}
