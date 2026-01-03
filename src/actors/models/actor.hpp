#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <t3d/t3dmodel.h>

struct Actor {
    int id;
    T3DVec3 scale;
    T3DVec3 position;
    T3DVec3 rotation;
    rspq_block_t *dpl;
    T3DMat4FP *modelMat;
    color_t color;
};

struct ActorBody {
    int id;
    T3DVec3 scale;
    T3DVec3 position;
    T3DVec3 rotation;
    rspq_block_t *dpl;
    T3DMat4FP *modelMat;
    color_t color;
    btRigidBody *rigidBody;
};
