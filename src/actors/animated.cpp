#include <t3d/t3danim.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dskeleton.h>
#include "animated.hpp"
#include "../physics/bodyForce.hpp"
#include "../physics/bodyMovement.hpp"
#include "../physics/convertBullet.hpp"
#include "models/actions.hpp"
#include "../utility/button.hpp"

void Animated::drawAnimatedBody(ComplexBody *body) {
    t3d_skeleton_update(&body->skeleton);

    body->position = convertBullet::btVector3ToT3DVec3(_physics.getRigidBodyPosition(body->rigidBody));
    _physics.setRigidBodyRotation(body->rigidBody, body->rotation.v);
    //body->rotation = convertBullet::btQuaternionToT3DVec3(_physics.getRigidBodyRotation(body->rigidBody));

    body->position.v[1] = body->position.v[1] - 8.25f;
    t3d_mat4fp_from_srt_euler(body->modelMat4FP, body->scale, body->rotation, body->position);

    rspq_block_run(body->rspBlock);
}

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
        .animBackFlip = t3d_anim_create(model, "Kick_Back_Flip"),
        .animWalk = t3d_anim_create(model, "Walk"),
        .animJump = t3d_anim_create(model, "Jump_From_Stand"),
        .animKickIdle = t3d_anim_create(model, "Idle_Kick"),
        .animKickSwift = t3d_anim_create(model, "Kick_Swift"),
        .animKickCrescent = t3d_anim_create(model, "Kick_Spin_Crescent"),
        .animKickHeel = t3d_anim_create(model, "Kick_Spin_Heel"),
        .animKickLow = t3d_anim_create(model, "Kick_Spin_Low"),
        .animKickToe = t3d_anim_create(model, "Kick_Toe")
    };

    T3DVec3 defaultSize = (T3DVec3){{ 2.75f, 7.25f, 2.75f}};

    complexBody.rigidBody = _physics.createCubeRigidBody(complexBody.position.v, defaultSize.v, 10.0f);

    complexBody.skeletonBlend = t3d_skeleton_clone(&complexBody.skeleton, false);

    t3d_anim_attach(&complexBody.animIdle, &complexBody.skeleton);

    t3d_anim_attach(&complexBody.animWalk, &complexBody.skeletonBlend);

    t3d_anim_attach(&complexBody.animKickIdle, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animJump, false);
    t3d_anim_set_playing(&complexBody.animJump, false);
    t3d_anim_attach(&complexBody.animJump, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animBackFlip, false);
    t3d_anim_set_playing(&complexBody.animBackFlip, false);
    t3d_anim_attach(&complexBody.animBackFlip, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animKickSwift, false);
    t3d_anim_set_playing(&complexBody.animKickSwift, false);
    t3d_anim_attach(&complexBody.animKickSwift, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animKickCrescent, false);
    t3d_anim_set_playing(&complexBody.animKickCrescent, false);
    t3d_anim_attach(&complexBody.animKickCrescent, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animKickHeel, false);
    t3d_anim_set_playing(&complexBody.animKickHeel, false);
    t3d_anim_attach(&complexBody.animKickHeel, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animKickLow, false);
    t3d_anim_set_playing(&complexBody.animKickLow, false);
    t3d_anim_attach(&complexBody.animKickLow, &complexBody.skeleton);

    t3d_anim_set_looping(&complexBody.animKickToe, false);
    t3d_anim_set_playing(&complexBody.animKickToe, false);
    t3d_anim_attach(&complexBody.animKickToe, &complexBody.skeleton);

    rspq_block_begin();
        t3d_matrix_push(complexBody.modelMat4FP);
        rdpq_set_prim_color(complexBody.color);
        t3d_model_draw_skinned(model, &complexBody.skeleton);

        t3d_matrix_pop(1);
    complexBody.rspBlock = rspq_block_end();

    t3d_mat4fp_from_srt_euler(complexBody.modelMat4FP, complexBody.scale, complexBody.rotation, complexBody.position);

    return complexBody;
}

void Animated::updateAnimatedBodyControls(ComplexBody *body) {
    joypad_inputs_t joypadInput = joypad_get_inputs(body->controlPort);

    if (joypadInput.btn.z && body->isKickMode && body->isHoldingZButton) {
        if (!body->isKicking) {
            auto button = Button::PriorityButtonQuery(joypadInput.btn);
            switch (button) {
                // A = Back Flip
                case Button::BUTTON_A:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Back_Flip;
                    t3d_anim_set_time(&body->animBackFlip, 0.0f);
                    t3d_anim_set_playing(&body->animBackFlip, true);
                    break;
                // B = Swift Kick
                case Button::BUTTON_B:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Swift;
                    t3d_anim_set_time(&body->animKickSwift, 0.0f);
                    t3d_anim_set_playing(&body->animKickSwift, true);
                    break;
                // C-Up = Crescent Kick
                case Button::BUTTON_C_UP:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Spin_Crescent;
                    t3d_anim_set_time(&body->animKickCrescent, 0.0f);
                    t3d_anim_set_playing(&body->animKickCrescent, true);
                    break;
                // C-Right = Heel Kick
                case Button::BUTTON_C_RIGHT:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Spin_Heel;
                    t3d_anim_set_time(&body->animKickHeel, 0.0f);
                    t3d_anim_set_playing(&body->animKickHeel, true);
                    //bodyForce::applyForce(body, (T3DVec3){{ 5.0f,5.0f, 5.0f }}, 20.0f);
                    break;
                // C-Down = Low Kick
                case Button::BUTTON_C_DOWN:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Spin_Low;
                    t3d_anim_set_time(&body->animKickLow, 0.0f);
                    t3d_anim_set_playing(&body->animKickLow, true);
                    break;
                // C-Left = Toe Kick
                case Button::BUTTON_C_LEFT:
                    body->isKicking = true;
                    body->activeKick = Kicks::Kick_Toe;
                    t3d_anim_set_time(&body->animKickToe, 0.0f);
                    t3d_anim_set_playing(&body->animKickToe, true);
                    break;
                case Button::BUTTON_NOPRESS:
                    break;
                default:
                    break;
            }
        }
    }
    else if (joypadInput.btn.z && body->isKickMode && !body->isHoldingZButton) {
        body->isHoldingZButton = true;
    }
    else if (joypadInput.btn.z && !body->isKickMode && !body->isHoldingZButton) {
        body->isKickMode = true;
        t3d_anim_set_playing(&body->animKickIdle, true);
    }
    else {
        body->isKickMode = false;
        body->isHoldingZButton = false;
        t3d_anim_set_playing(&body->animKickIdle, false);
    }

    T3DVec3 newDir = {{(float)joypadInput.stick_x * 0.05f,0.0f,(float)joypadInput.stick_y * 0.05f}};
    float speed = sqrtf(t3d_vec3_len2(&newDir));

    if (speed > 0.15f) {
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

    auto directionalVelocity = (T3DVec3){{-directionalVelocityX, 0.0f, directionalVelocityZ}};

    bodyMovement::movement(body, directionalVelocity);
    //float angularVelocity = directionalVelocity.v. / 1.75;  ;
    //bodyMovement::rotation(body, angularVelocity);
}

void Animated::render(ComplexBody *body, float deltaTime) {
    t3d_anim_update(&body->animIdle, deltaTime);

    t3d_anim_update(&body->animWalk, deltaTime);

    if (body->isKickMode && body->isHoldingZButton) {
        t3d_anim_update(&body->animKickIdle, deltaTime);
    }
    else {
        t3d_anim_set_speed(&body->animWalk, body->animBlend + 0.15f);
        t3d_anim_update(&body->animWalk, deltaTime);
        t3d_skeleton_blend(&body->skeleton, &body->skeleton, &body->skeletonBlend, body->animBlend);
    }
    if (body->isKicking) {
        switch (body->activeKick) {
            // A = Back Flip
            case Kicks::Kick_Back_Flip:
                if (t3d_anim_is_playing(&body->animBackFlip)) {
                    t3d_anim_update(&body->animBackFlip, deltaTime);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animBackFlip, false);
                }
                break;
            // B = Swift Kick
            case Kicks::Kick_Swift:
                if (t3d_anim_is_playing(&body->animKickSwift)) {
                    t3d_anim_update(&body->animKickSwift, deltaTime);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animKickSwift, false);
                }
                break;
            // C-Up = Crescent Kick
            case Kicks::Kick_Spin_Crescent:
                if (t3d_anim_is_playing(&body->animKickCrescent)) {
                    t3d_anim_update(&body->animKickCrescent, deltaTime);
                }
                else if (t3d_anim_get_time(&body->animKickCrescent) == 1.0f) {
                    t3d_anim_set_playing(&body->animKickCrescent, false);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animKickCrescent, false);
                }
                break;
            // C-Right = Heel Kick
            case Kicks::Kick_Spin_Heel:
                if (t3d_anim_is_playing(&body->animKickHeel)) {
                    t3d_anim_update(&body->animKickHeel, deltaTime);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animKickHeel, false);
                }
                break;
            // C-Down = Low Kick
            case Kicks::Kick_Spin_Low:
                if (t3d_anim_is_playing(&body->animKickLow)) {
                    t3d_anim_update(&body->animKickLow, deltaTime);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animKickLow, false);
                }
                break;
            // C-Left = Toe Kick
            case Kicks::Kick_Toe:
                if (t3d_anim_is_playing(&body->animKickToe)) {
                    t3d_anim_update(&body->animKickToe, deltaTime);
                }
                else {
                    body->isKicking = false;
                    t3d_anim_set_playing(&body->animKickToe, false);}
                break;
            default:
                break;
        }
    }
}

void Animated::deleteAnimatedBody(ComplexBody *body) {
    t3d_skeleton_destroy(&body->skeleton);
    t3d_skeleton_destroy(&body->skeletonBlend);

    t3d_anim_destroy(&body->animIdle);
    t3d_anim_destroy(&body->animWalk);
    t3d_anim_destroy(&body->animKickSwift);
    t3d_anim_destroy(&body->animJump);
    t3d_anim_destroy(&body->animKickIdle);
}
