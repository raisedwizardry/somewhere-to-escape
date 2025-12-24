#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>

namespace bodyMovement {

    inline void movement(ComplexBody* body, T3DVec3 directionalVelocity) {
        body->rigidBody->setLinearVelocity(btVector3(directionalVelocity.v[0], directionalVelocity.v[1], directionalVelocity.v[2])); //setLinearVelocity(btVector3(30.0f, 0.0f, 0.0f));
    }

}
