#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>

namespace bodyMovement {

    inline void movement(ComplexBody* body, T3DVec3 directionalVelocity) {
        body->rigidBody->setLinearVelocity(btVector3(directionalVelocity.x, directionalVelocity.y, directionalVelocity.z));
    }

    // inline void speedBoost(ComplexBody* body, int8_t amount) {
    // }

}
