#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "basic.hpp"
#include "models/actor.hpp"


Actor Basic::createActor(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition) {
    Actor actor {
        .id = _counter.getIncrementedId(),
        .scale = scale,
        .position = startingPosition,
        .rotation = (T3DVec3){{0, 0, 0}},
        .modelMat = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
        .color = RGBA32(0, 255, 0, 255)
    };

    rspq_block_begin();
        t3d_matrix_push(actor.modelMat);
        rdpq_set_prim_color(actor.color);
        t3d_model_draw(model);
        t3d_matrix_pop(1);
    actor.dpl = rspq_block_end();

    t3d_mat4fp_from_srt_euler(actor.modelMat, actor.scale, actor.rotation, actor.position);

    return actor;
}

void Basic::drawActor(Actor *actor, T3DVec3 position, T3DVec3 rotation) {
    rspq_block_run(actor->dpl);
    actor->position = position;
    actor->rotation = rotation;
    t3d_mat4fp_from_srt_euler(actor->modelMat, actor->scale, actor->rotation, actor->position);
}
