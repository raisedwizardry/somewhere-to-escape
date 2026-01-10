#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
#include "actions.hpp"

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
    T3DAnim animBackFlip;
    T3DAnim animWalk;
    T3DAnim animJump;
    T3DAnim animKickIdle;
    T3DAnim animKickSwift;
    T3DAnim animKickCrescent;
    T3DAnim animKickHeel;
    T3DAnim animKickLow;
    T3DAnim animKickToe;
    float animBlend = 0.0f;
    bool isHoldingZButton = false;
    bool isAbleToKick = false;
    bool isKickMode = false;
    Kicks activeKick;
    bool isKicking = false;
    bool isWalking = false;
    bool isRunning = false;
    bool isJumping = false;
    float currentSpeed = 0.0f;
    T3DVec3 movementDirection = (T3DVec3){{0.0f, 0.0f, 0.0f}};
    float attackTimer;
    float jumpTimer;
    rspq_block_t *rspBlock;
    btRigidBody *rigidBody;
};

