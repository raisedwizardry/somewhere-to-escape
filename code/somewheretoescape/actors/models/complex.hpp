#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3danim.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>

struct ComplexBody {
    T3DVec3 scale;
    T3DVec3 position;
    T3DVec3 rotation;
    joypad_port_t controlPort;
    T3DMat4FP *modelMat4FP;
    color_t color;
    T3DSkeleton skeleton;
    T3DSkeleton skeletonBlend;
    T3DAnim animIdle;
    T3DAnim animWalk;
    T3DAnim animJump;
    T3DAnim animAttack;
    float animBlend = 0.0f;
    bool isAttack = false;
    bool isJump = false;
    float currentSpeed = 0.0f;
    T3DVec3 movementDirection = (T3DVec3){{0.15f, 0.15f, 0.15f}};
    float attackTimer;
    float jumpTimer;
    rspq_block_t *rspBlock;
    btRigidBody *rigidBody;
};
