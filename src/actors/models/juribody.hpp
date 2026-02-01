#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
#include "actions.hpp"

struct JuriBody {
    T3DVec3 scale;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DMat4FP *modelMat4FP;
    T3DSkeleton skeleton;
    T3DSkeleton skeletonBlend;
    T3DAnim animIdle;
    T3DAnim animWalk;
    T3DAnim animThrow;
    T3DAnim animSwing;
    T3DAnim animBlock;
    T3DAnim animFightIdle;
    T3DAnim animSideHit;
    float animBlend = 0.0f;
    rspq_block_t *rspBlock;
    btRigidBody *rigidBody;
};
