#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>
#include "../actors/models/complex.hpp"

namespace bodyMovement {

    inline void movement(ComplexBody* body, T3DVec3 directionalVelocity) {
        body->rigidBody->setLinearVelocity(btVector3(directionalVelocity.x, directionalVelocity.y, directionalVelocity.z));
    }

    inline void rotation(ComplexBody* body, T3DVec3 angularVelocity) {
        auto btAngularVelocity = btVector3(angularVelocity.x, angularVelocity.y, angularVelocity.z);
        body->rigidBody->setAngularVelocity(btAngularVelocity);
    }

}
