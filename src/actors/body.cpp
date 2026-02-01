#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "body.hpp"
#include "models/actor.hpp"
#include "../physics/convertBullet.hpp"

ActorBody Body::createActorBody(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation, T3DVec3 size, float mass) {
    ActorBody actor = {
        .id = _counter.getIncrementedId(),
        .scale = scale,
        .position = startingPosition,
        .rotation = startingRotation,
        .modelMat = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
    };

    actor.rigidBody = _physics.createCubeRigidBody(startingPosition.v, size.v, mass);

    rspq_block_begin();
        t3d_matrix_push(actor.modelMat);
        t3d_model_draw(model);
        t3d_matrix_pop(1);
    actor.dpl = rspq_block_end();

    t3d_mat4fp_from_srt_euler(actor.modelMat, actor.scale, actor.rotation, actor.position);

    return actor;
}

void Body::drawActorBody(ActorBody *actor) {
    actor->position = convertBullet::btVector3ToT3DVec3(_physics.getRigidBodyPosition(actor->rigidBody));
    actor->rotation = convertBullet::btQuaternionToT3DVec3(_physics.getRigidBodyRotation(actor->rigidBody));
    actor->position.v[1] = actor->position.v[1];

    rspq_block_run(actor->dpl);

    t3d_mat4fp_from_srt_euler(actor->modelMat, actor->scale, actor->rotation, actor->position);
}
