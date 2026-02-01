#include "actors.hpp"
#include "../scene/camera.hpp"
#include "./models/actor.hpp"
#include "../scene/time.hpp"

void Actors::updateActorsControls() {
    _animated.updateAnimatedBodyControls(&_animated.escapePlayer1);
}

void Actors::createActors() {
    float scale64 = 0.015625f;
    auto defaultScale = (T3DVec3){{scale64, scale64, scale64}};
    auto defaultRotation = (T3DVec3){{0.0f, 0.0f, 0.0f}};
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
    auto playerStartPosition = (T3DVec3){{0.0f, 0.0f, 0.0f}};

    _animated.escapePlayer1 = _animated.createAnimatedBody(Player1ModelToUse, defaultScale, playerStartPosition, defaultRotation,  JOYPAD_PORT_1);

     // actorBodys.push_back(
     //     _body.createActorBody(juriModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[5])
     // );

    T3DVec3 dwellerPositions[] = {
        (T3DVec3){{32.0f, 0.0f, 32.0f}},
        (T3DVec3){{0.0f, 0.0f, 32.0f}},
        (T3DVec3){{-32.0f, 0.0f, 32.0f}},
        (T3DVec3){{0.0f, 0.0f, 64.0f}},
    };
    auto dwellerSize = (T3DVec3){{2.1f, 2.1f, 2.1f}};

    //_dweller.dweller1 = _dweller.createDwellerBody(defaultScale, dwellerPositions[0], defaultRotation, dwellerSize, 10.0f);
    // _dweller.dweller2 = _dweller.createDwellerBody(defaultScale, dwellerPositions[1], defaultRotation, dwellerSize, 10.0f);
    // _dweller.dweller3 = _dweller.createDwellerBody(defaultScale, dwellerPositions[2], defaultRotation, dwellerSize, 10.0f);
     _dweller.dweller4 = _dweller.createDwellerBody(defaultScale, dwellerPositions[3], defaultRotation, dwellerSize, 10.0f);

    actorBodys.push_back(
        _body.createActorBody(nModel, (T3DVec3){{nScale, nScale, nScale}}, (T3DVec3){{0.0f, 0.0f, 32.0f}}, defaultRotation, (T3DVec3){{4.0f, 4.0f, 4.0f}}, 20.0f)
    );

    auto caveLocation = (T3DVec3){{40.0f, 0.0f, 80.0f}};
    auto caveSize = (T3DVec3){{27.0f, 14.0f, 54.0f}};

    actorBodys.push_back(
        _body.createActorBody(caveModel, defaultScale, caveLocation, defaultRotation, caveSize, 0.0f)
    );

    // actorBodys.push_back(
    //     _body.createActorBody(markerModel, defaultScale, blockPositions[2])
    // );

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

     //_dweller.render(&_dweller.dweller1, _time.deltaTime);
    // _dweller.render(&_dweller.dweller2, _time.deltaTime);
    // _dweller.render(&_dweller.dweller3, _time.deltaTime);
    _dweller.render(&_dweller.dweller4, _time.deltaTime);
    //
    //_dweller.drawDwellerBody(&_dweller.dweller1);
    // _dweller.drawDwellerBody(&_dweller.dweller2);
    // _dweller.drawDwellerBody(&_dweller.dweller3);
    _dweller.drawDwellerBody(&_dweller.dweller4);

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
