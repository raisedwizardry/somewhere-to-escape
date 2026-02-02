#include "actors.hpp"
#include "../scene/camera.hpp"
#include "./models/actor.hpp"
#include "../scene/time.hpp"

void Actors::updateActorsControls() {
    _animated.updateAnimatedBodyControls(&escapePlayer1);
}

void Actors::createActors() {
    float scale64 = 0.0156f; // 0.015625f;
    auto defaultScale = (T3DVec3){{scale64, scale64, scale64}};
    auto defaultRotation = (T3DVec3){{0.0f, 0.0f, 0.0f}};
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
    auto playerStartPosition = (T3DVec3){{0.0f, 0.0f, -125.0f}};

    escapePlayer1 = _animated.createAnimatedBody(Player1ModelToUse, defaultScale, playerStartPosition, defaultRotation,  JOYPAD_PORT_1);

    auto caveLocation = (T3DVec3){{20.0f, 0.0f, 25.0f}};
    auto caveSize = (T3DVec3){{27.0f, 14.0f, 54.0f}};
    cave = _body.createActorBody(caveModel, defaultScale, caveLocation, defaultRotation, caveSize, 0.0f);

    // auto markerSize = (T3DVec3){{2.1f, 2.1f, 2.1f}};
    // actorBodys.push_back(
    //     _body.createActorBody(markerModel, defaultScale, (T3DVec3){{4.0f, 0.0f, 10.0f}}, defaultRotation, markerSize, 0.0f)
    // );

    T3DVec3 dwellerPositions[] = {
        (T3DVec3){{-35.0f, 0.0f, 100.0f}},
        (T3DVec3){{-50.0f, 0.0f, 100.0f}},
    };
    auto dwellerSize = (T3DVec3){{2.1f, 2.1f, 2.1f}};

    dweller1 = _dweller.createDwellerBody(defaultScale, dwellerPositions[0], defaultRotation, dwellerSize, 0.0f);
    dweller2 = _dweller.createDwellerBody(defaultScale, dwellerPositions[1], defaultRotation, dwellerSize, 0.0f);

    auto pathLocation = (T3DVec3){{-40.0f, 0.0f, 125.0f}};
    auto pathSize = (T3DVec3){{27.0f, 14.0f, 10.0f}};
    path = _body.createActorBody(pathModel, defaultScale, pathLocation, defaultRotation, pathSize, 0.0f);

    // float nScale = 0.11f;
    // actorBodys.push_back(
    //     _body.createActorBody(nModel, (T3DVec3){{nScale, nScale, nScale}}, (T3DVec3){{0.0f, 0.0f, 32.0f}}, defaultRotation, (T3DVec3){{4.0f, 4.0f, 4.0f}}, 20.0f)
    // );

    auto juriLocation = (T3DVec3){{20.0f, 0.0f, 230.0f}};
    auto juriRotation = (T3DVec3){{0.0f, M_PI, 0.0f}};
    theJuri = _juri.createJuriBody(defaultScale, juriLocation, juriRotation);

    auto trainLocation = (T3DVec3){{40.0f, 0.0f, 250.0f}};
    auto trainSize = (T3DVec3){{20.0f, 14.0f, 10.0f}};
    train = _body.createActorBody(trainModel, defaultScale, trainLocation, defaultRotation, trainSize, 0.0f);

    if (_debug.P4_CAMERA_DEBUG) {
        _camera.cameraTarget = escapePlayer1.position;
        _camera.cameraPosition = (T3DVec3){{escapePlayer1.position.x, 25.0f, escapePlayer1.position.z + 60.0f}};
    }
}

void Actors::drawActors(GameState gameState) {
    _animated.render(&escapePlayer1, _time.deltaTime);
    if (!_debug.P4_CAMERA_DEBUG) {
        _camera.cameraTarget = escapePlayer1.position;
        _camera.cameraPosition = (T3DVec3){{escapePlayer1.position.x, 25.0f, escapePlayer1.position.z - 60.0f}};
    }

    _animated.drawAnimatedBody(&escapePlayer1);

    // for (ActorBody actorBody : actorBodys) {
    //     _body.drawActorBody(&actorBody);
    // }
    if (gameState == LEVEL_1) {
        _body.drawActorBody(&cave);
    }
    else if (gameState == LEVEL_2) {
        _body.drawActorBody(&path);
        _dweller.render(&dweller1, _time.deltaTime);
        _dweller.render(&dweller2, _time.deltaTime);

        _dweller.drawDwellerBody(&dweller1);
        _dweller.drawDwellerBody(&dweller2);
    }
    else if (gameState == LEVEL_3) {
        _body.drawActorBody(&train);
        _juri.render(&theJuri, _time.deltaTime);
        _juri.drawJuriBody(&theJuri);
    }

    showOnScreenDebug();
}

void Actors::deleteActors() {
    for (Actor actor : actors) {
        rspq_block_free(actor.dpl);

        free_uncached(actor.modelMat);
    }

    for (ActorBody actorBody : actorBodys) {
        rspq_block_free(actorBody.dpl);

        free_uncached(actorBody.modelMat);
        delete actorBody.rigidBody;
    }
}

void Actors::showOnScreenDebug() {
    float posX = 8;
    if (_debug.ONSCREEN_DEBUG) {
        // float posX1 = 16;
        // float posX2 = 24;
        // float posX3 = 40;
        // float posX4 = 56;
        float otherPosX = 32;
        float otherPosY1 = 64;
        float otherPosY2 = 80;
        float otherPosY3 = 96;
        float otherPosY4 = 112;
        float otherPosY5 = 128;
        float otherPosY6 = 144;
        float otherPosY7 = 160;
        float otherPosY8 = 176;
        float otherPosY9 = 192;
        float otherPosY10 = 210;
        float otherPosY11 = 226;
        float otherPosY12 = 234;

        rdpq_sync_pipe();
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY1, "rX:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY1, std::to_string(escapePlayer1.rotation.x).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY2, "rY:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY2, std::to_string(escapePlayer1.rotation.y).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY3, "rZ:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY3, std::to_string(escapePlayer1.rotation.z).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY4, "pX:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY4, std::to_string(escapePlayer1.position.x).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY5, "pY:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY5, std::to_string(escapePlayer1.position.y).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY6, "pZ:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY6, std::to_string(escapePlayer1.position.z).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY7, "7:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY7, std::to_string(t3d_anim_get_time(&escapePlayer1.animKickCrescent)).c_str() );
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY8, "8:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY8, "Debug");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY9, "9:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY9, "Debug");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY10, "10:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY10, "Debug");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY11, "11:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY11, "Debug");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY12, "12:");
        rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY12, "Debug");
    }
}

Actors::~Actors() {
    deleteActors();
}
