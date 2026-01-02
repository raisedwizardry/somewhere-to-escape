#include <t3d/t3danim.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dskeleton.h>
#include "animated.hpp"
#include "../physics/bodyMovement.hpp"
#include "../physics/convertT3D.hpp"

ComplexBody Animated::createAnimatedBody(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation,  joypad_port_t controlPort) {
    ComplexBody complexBody = {
        .scale = scale,
        .position = startingPosition,
        .rotation = startingRotation,
        .controlPort = controlPort,
        .modelMat4FP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP)),
        .color = RGBA32(255, 255, 255, 255),
        .skeleton = t3d_skeleton_create(model),
        .animIdle = t3d_anim_create(model, "Idle_Stand"),
        .animWalk = t3d_anim_create(model, "Walk"),
        .animJump = t3d_anim_create(model, "Jump_From_Stand"),
        .animAttack = t3d_anim_create(model, "Kick_Swift")
    };

    complexBody.rigidBody = _physics.createCubeRigidBody(complexBody.position.v, defaultSize.v, 1.0f);

    complexBody.skeletonBlend = t3d_skeleton_clone(&complexBody.skeleton, false);

    t3d_anim_attach(&complexBody.animIdle, &complexBody.skeleton);

    t3d_anim_attach(&complexBody.animWalk, &complexBody.skeletonBlend);

    t3d_anim_set_looping(&complexBody.animJump, false);
    t3d_anim_set_playing(&complexBody.animJump, false);
    t3d_anim_attach(&complexBody.animJump, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animAttack, false);
    t3d_anim_set_playing(&complexBody.animAttack, false);
    t3d_anim_attach(&complexBody.animAttack, &complexBody.skeleton);

    rspq_block_begin();
        t3d_matrix_push(complexBody.modelMat4FP);
        rdpq_set_prim_color(complexBody.color);
        t3d_model_draw_skinned(model, &complexBody.skeleton);

        t3d_matrix_pop(1);
    complexBody.rspBlock = rspq_block_end();

    return complexBody;
}

void Animated::updateAnimatedBodyControls(ComplexBody *body) {
    joypad_inputs_t joypadInput = joypad_get_inputs(body->controlPort);

    T3DVec3 newDir = {{
        (float)joypadInput.stick_x * 0.05f,
        0,
        -(float)joypadInput.stick_y * 0.05f
    }};
    float speed = sqrtf(t3d_vec3_len2(&newDir));

    if (joypadInput.btn.b && !body->animAttack.isPlaying && !body->animJump.isPlaying) {
        t3d_anim_set_playing(&body->animAttack, true);
        t3d_anim_set_time(&body->animAttack, 0.0f);
        body->isAttack = true;
    }

    if (joypadInput.btn.a && !body->animJump.isPlaying && !body->animAttack.isPlaying) {
        t3d_anim_set_playing(&body->animJump, true);
        t3d_anim_set_time(&body->animJump, 0.0f);
        body->isJump = true;
    }

    if (speed > 0.15f && !body->isAttack) {
        newDir.v[0] /= speed;
        newDir.v[2] /= speed;
        body->movementDirection = newDir;

        float newAngle = atan2f(body->movementDirection.v[0], body->movementDirection.v[2]);
        body->rotation.v[1] = t3d_lerp_angle(body->rotation.v[1], newAngle, 0.25f);
        body->currentSpeed = t3d_lerp(body->currentSpeed, speed * 0.15f, 0.15f);
    }
    else {
        body->currentSpeed *= 0.8f;
    }

    body->animBlend = body->currentSpeed / 0.51f;
    if (body->animBlend > 1.0f) {
        body->animBlend = 1.0f;
    }

    float directionalVelocityX = body->movementDirection.v[0] * body->currentSpeed * 25.0f;
    float directionalVelocityZ = body->movementDirection.v[2] * body->currentSpeed * 25.0f;

    auto directionalVelocity = (T3DVec3){{directionalVelocityX, 0.0f, directionalVelocityZ}};

    bodyMovement::movement(body, directionalVelocity);
}

void Animated::render(ComplexBody *body, float deltaTime) {
    t3d_anim_update(&body->animIdle, deltaTime);
    t3d_anim_set_speed(&body->animWalk, body->animBlend + 0.15f);
    t3d_anim_update(&body->animWalk, deltaTime);

    if (body->isAttack) {
        t3d_anim_update(&body->animAttack, deltaTime);
        if (!body->animAttack.isPlaying) {
            body->isAttack = false;
        }
    }

    if (body->isJump) {
        t3d_anim_update(&body->animJump, deltaTime);
        if (!body->animJump.isPlaying) {
            body->isJump = false;
        }
    }

    t3d_skeleton_blend(&body->skeleton, &body->skeleton, &body->skeletonBlend, body->animBlend);
}

void Animated::drawAnimatedBody(ComplexBody *body) {
    t3d_skeleton_update(&body->skeleton);

    body->position = convertT3D::btVector3ToT3DVec3(_physics.getRigidBodyPosition(body->rigidBody));
    _physics.setRigidBodyRotation(body->rigidBody, body->rotation.v);
    //body->rotation = convertT3D::btQuaternionToT3DVec3(_physics.getRigidBodyRotation(body->rigidBody));

    t3d_mat4fp_from_srt_euler(body->modelMat4FP, body->scale, -body->rotation, body->position);

    rspq_block_run(body->rspBlock);
}

void Animated::deleteAnimatedBody(ComplexBody *body) {
    t3d_skeleton_destroy(&body->skeleton);
    t3d_skeleton_destroy(&body->skeletonBlend);

    t3d_anim_destroy(&body->animIdle);
    t3d_anim_destroy(&body->animWalk);
    t3d_anim_destroy(&body->animAttack);
    t3d_anim_destroy(&body->animJump);
}
