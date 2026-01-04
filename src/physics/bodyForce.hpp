#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>
#include "../actors/models/complex.hpp"

namespace bodyMovement {

    inline void movement(ComplexBody* body, T3DVec3 directionalVelocity) {
        body->rigidBody->setLinearVelocity(btVector3(directionalVelocity.v[0], directionalVelocity.v[1], directionalVelocity.v[2]));
    }

    inline void applyForce(ComplexBody* body, T3DVec3 direction, float amount) {
        body->rigidBody->applyForce(btVector3(direction.x, direction.y, direction.z), btVector3(amount, amount, amount)); //setLinearVelocity(btVector3(30.0f, 0.0f, 0.0f));
    }

}
