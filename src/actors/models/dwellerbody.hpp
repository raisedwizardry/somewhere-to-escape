#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
#include "actions.hpp"

struct DwellerBody {
    T3DVec3 scale;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DMat4FP *modelMat4FP;
    T3DSkeleton skeleton;
    T3DAnim animFlail;
    rspq_block_t *rspBlock;
    btRigidBody *rigidBody;
};
