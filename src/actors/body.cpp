#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "body.hpp"
#include "models/actor.hpp"
#include "../physics/convertBullet.hpp"

ActorBody Body::createActorBody(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition) {
    ActorBody actor = {
        .id = _counter.getIncrementedId(),
        .scale = scale,
        .position = startingPosition,
        .rotation = (T3DVec3){{0.0f, 0.0f, 0.0f}},
        .modelMat = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
    };

    T3DVec3 size = (T3DVec3){{16.0f,16.0f, 16.0f}};
    actor.rigidBody = _physics.createCubeRigidBody(startingPosition.v, size.v, 1.0f);

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

    rspq_block_run(actor->dpl);

    t3d_mat4fp_from_srt_euler(actor->modelMat, actor->scale, actor->rotation, actor->position);
}
