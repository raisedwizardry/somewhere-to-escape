#include "juri.hpp"

#include <t3d/t3d.h>
#include "../physics/convertBullet.hpp"

JuriBody Juri::createJuriBody(T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation) {
    JuriBody juri = {
        .scale = scale,
        .position = startingPosition,
        .rotation = startingRotation,
        .modelMat4FP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
        .skeleton = t3d_skeleton_create(juriModel),
        .animIdle = t3d_anim_create(juriModel, "Idle"),
        .animWalk = t3d_anim_create(juriModel, "Strut Walking"),
        .animThrow = t3d_anim_create(juriModel, "Throwing"),
        .animSwing = t3d_anim_create(juriModel, "Heavy Weapon swing"),
        .animBlock = t3d_anim_create(juriModel, "Block"),
        .animFightIdle = t3d_anim_create(juriModel, "Boxing Idle"),
        .animSideHit = t3d_anim_create(juriModel, "Big Side Hit")
    };

    T3DVec3 defaultSize = (T3DVec3){{ 3.5f, 8.0f, 3.5f}};

    juri.rigidBody = _physics.createCubeRigidBody(startingPosition.v, defaultSize.v, 30.0f);

    t3d_anim_attach(&juri.animIdle, &juri.skeleton);

    t3d_anim_attach(&juri.animWalk, &juri.skeletonBlend);

    t3d_anim_attach(&juri.animFightIdle, &juri.skeleton);

    t3d_anim_set_looping(&juri.animThrow, false);
    t3d_anim_set_playing(&juri.animThrow, false);
    t3d_anim_attach(&juri.animThrow, &juri.skeleton);

    t3d_anim_set_looping(&juri.animSwing, false);
    t3d_anim_set_playing(&juri.animSwing, false);
    t3d_anim_attach(&juri.animSwing, &juri.skeleton);

    t3d_anim_set_looping(&juri.animBlock, false);
    t3d_anim_set_playing(&juri.animBlock, false);
    t3d_anim_attach(&juri.animBlock, &juri.skeleton);

    t3d_anim_set_looping(&juri.animSideHit, false);
    t3d_anim_set_playing(&juri.animSideHit, false);
    t3d_anim_attach(&juri.animSideHit, &juri.skeleton);

    rspq_block_begin();
        t3d_matrix_push(juri.modelMat4FP);
        t3d_model_draw_skinned(juriModel, &juri.skeleton);

        t3d_matrix_pop(1);
    juri.rspBlock = rspq_block_end();

    t3d_mat4fp_from_srt_euler(juri.modelMat4FP, juri.scale, juri.rotation, juri.position);

    return juri;
}
void Juri::render(JuriBody *juri, float deltaTime) {
    t3d_anim_update(&juri->animIdle, deltaTime);
    //t3d_anim_update(&juri->animWalk, deltaTime);
}

void Juri::drawJuriBody(JuriBody *juri) {
    t3d_skeleton_update(&juri->skeleton);

    juri->position = convertBullet::btVector3ToT3DVec3(_physics.getRigidBodyPosition(juri->rigidBody));
    //juri->rotation = convertBullet::btQuaternionToT3DVec3(_physics.getRigidBodyRotation(juri->rigidBody));
    _physics.setRigidBodyRotation(juri->rigidBody, juri->rotation.v);

    juri->position.v[1] = juri->position.v[1] - 9.0f;

    t3d_mat4fp_from_srt_euler(juri->modelMat4FP, juri->scale, juri->rotation, juri->position);

    rspq_block_run(juri->rspBlock);
}
