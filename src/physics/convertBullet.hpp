#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3d.h>

namespace convertBullet {

    inline T3DVec3 btQuaternionToT3DVec3(btQuaternion quaternion) {
        return (T3DVec3){{ quaternion.getX(), quaternion.getY(), quaternion.getZ() }};
    }

    inline T3DVec3 btVector3ToT3DVec3(btVector3 vector) {
        return (T3DVec3){{ vector.getX(), vector.getY(), vector.getZ() }};
    }

}
