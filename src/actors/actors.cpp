#include "actors.hpp"
#include "../scene/camera.hpp"
#include "./models/actor.hpp"
#include "../scene/time.hpp"

void Actors::updateActorsControls() {
    _animated.updateAnimatedBodyControls(&_animated.escapePlayer1);
}

void Actors::createActors() {
    T3DVec3 blockPositions[] = {
        (T3DVec3){{32.0f, 0.0f, 32.0f}},

        (T3DVec3){{0.0f, 0.0f, 32.0f}},
        (T3DVec3){{-32.0f, 0.0f, 32.0f}},

        (T3DVec3){{32.0f, 0.0f, 0.0f}},
        (T3DVec3){{32.0f, 0.0f, -32.0f}},

        (T3DVec3){{0.0f, 0.0f, 0.0f}},
        (T3DVec3){{0.0f, 0.0f, -32.0f}},

        (T3DVec3){{-32.0f, 0.0f, 0.0f}},
        (T3DVec3){{-32.0f, 0.0f, -32.0f}},

        (T3DVec3){{32.0f, 32.0f, 32.0f}},
        (T3DVec3){{32.0f, 32.0f, 0.0f}},
        (T3DVec3){{32.0f, 32.0f, -32.0f}},
        (T3DVec3){{0.0f, 32.0f, 32.0f}},
        (T3DVec3){{0.0f, 32.0f, 0.0f}},
        (T3DVec3){{0.0f, 32.0f, -32.0f}},
        (T3DVec3){{-32.0f, 32.0f, 32.0f}},
        (T3DVec3){{-32.0f, 32.0f, 0.0f}},
        (T3DVec3){{-32.0f, 32.0f, -32.0f}},

        (T3DVec3){{32.0f, 64.0f, 32.0f}},
        (T3DVec3){{32.0f, 64.0f, 0.0f}},
        (T3DVec3){{32.0f, 64.0f, -32.0f}},
        (T3DVec3){{0.0f, 64.0f, 32.0f}},
        (T3DVec3){{0.0f, 64.0f, 0.0f}},
        (T3DVec3){{0.0f, 64.0f, -32.0f}},
        (T3DVec3){{-32.0f, 64.0f, 32.0f}},
        (T3DVec3){{-32.0f, 64.0f, 0.0f}},
        (T3DVec3){{-32.0f, 64.0f, -32.0f}}
    };

    float juriScale = 0.015625f;
    float nScale = 0.11f;

    switch (selectedCharacter) {
        case BUNNY:
            Player1ModelToUse = t3d_model_load("rom:/bunny.t3dm");
            break;
        case SQUIR:
            Player1ModelToUse = t3d_model_load("rom:/squir.t3dm");
            break;
        case RAM:
        default:
            Player1ModelToUse = t3d_model_load("rom:/ram.t3dm");
            break;
    }
    _animated.escapePlayer1 = _animated.createAnimatedBody(Player1ModelToUse, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[0],(T3DVec3){{0.0f, 0.0f, 0.0f}},  JOYPAD_PORT_1);

     // actorBodys.push_back(
     //     _body.createActorBody(juriModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[5])
     // );
     // actorBodys.push_back(
     //     _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[8])
     // );
     // actorBodys.push_back(
     //     _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[9])
     // );
     // actorBodys.push_back(
     //     _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[7])
     // );
    actorBodys.push_back(
        _body.createActorBody(nModel, (T3DVec3){{nScale, nScale, nScale}}, blockPositions[6])
    );
    actorBodys.push_back(
        _body.createActorBody(caveModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[8])
    );

    actorBodys.push_back(
        _body.createActorBody(markerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[2])
    );

    if (_debug.P4_CAMERA_DEBUG) {
        _camera.cameraTarget = _animated.escapePlayer1.position;
        _camera.cameraPosition = (T3DVec3){{_animated.escapePlayer1.position.x, 25.0f, _animated.escapePlayer1.position.z + 60.0f}};
    }

}

void Actors::drawActors() {
    mixer_try_play();

    _animated.render(&_animated.escapePlayer1, _time.deltaTime);
    if (!_debug.P4_CAMERA_DEBUG) {
        _camera.cameraTarget = _animated.escapePlayer1.position;
        _camera.cameraPosition = (T3DVec3){{_animated.escapePlayer1.position.x, 25.0f, _animated.escapePlayer1.position.z - 60.0f}};
    }

    _animated.drawAnimatedBody(&_animated.escapePlayer1);

    for (ActorBody actorBody : actorBodys) {
        _body.drawActorBody(&actorBody);
    }

}

void Actors::deleteActors() {
    for (Actor actor : actors) {
        rspq_block_free(actor.dpl);

        free_uncached(actor.modelMat);
    }

    for (ActorBody actorBody : actorBodys) {
        rspq_block_free(actorBody.dpl);

        free_uncached(actorBody.modelMat);
    }
}

Actors::~Actors() {
    deleteActors();
}
