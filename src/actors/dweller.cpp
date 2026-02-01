#include "dweller.hpp"

#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "body.hpp"
#include "../physics/convertBullet.hpp"

DwellerBody Dweller::createDwellerBody(T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation, T3DVec3 size, float mass) {
    DwellerBody dweller = {
        .scale = scale,
        .position = startingPosition,
        .rotation = startingRotation,
        .modelMat4FP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
        .skeleton = t3d_skeleton_create(dwellerModel),
        .animFlail = t3d_anim_create(dwellerModel, "flail"),
    };

    t3d_anim_set_looping(&dweller.animFlail, true);
    t3d_anim_set_playing(&dweller.animFlail, true);
    t3d_anim_attach(&dweller.animFlail, &dweller.skeleton);

    dweller.rigidBody = _physics.createCubeRigidBody(startingPosition.v, size.v, mass);

    rspq_block_begin();
        t3d_matrix_push(dweller.modelMat4FP);
        t3d_model_draw_skinned(dwellerModel, &dweller.skeleton);

        t3d_matrix_pop(1);
    dweller.rspBlock = rspq_block_end();

    t3d_mat4fp_from_srt_euler(dweller.modelMat4FP, dweller.scale, dweller.rotation, dweller.position);

    return dweller;
}
void Dweller::render(DwellerBody *dweller, float deltaTime) {
    t3d_anim_update(&dweller->animFlail, deltaTime);
}

void Dweller::drawDwellerBody(DwellerBody *dweller) {
    t3d_skeleton_update(&dweller->skeleton);

    dweller->position = convertBullet::btVector3ToT3DVec3(_physics.getRigidBodyPosition(dweller->rigidBody));
    dweller->rotation = convertBullet::btQuaternionToT3DVec3(_physics.getRigidBodyRotation(dweller->rigidBody));

    t3d_mat4fp_from_srt_euler(dweller->modelMat4FP, dweller->scale, dweller->rotation, dweller->position);

    rspq_block_run(dweller->rspBlock);
}
