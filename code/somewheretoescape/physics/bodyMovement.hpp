#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmath.h>
#include "../actors/snake.hpp"

namespace bodyMovement {

    inline void movement(SnakeBody* snake, T3DVec3 directionalVelocity) {
        snake->rigidBody->setLinearVelocity(btVector3(directionalVelocity.v[0], directionalVelocity.v[1], directionalVelocity.v[2])); //setLinearVelocity(btVector3(30.0f, 0.0f, 0.0f));
    }

}
