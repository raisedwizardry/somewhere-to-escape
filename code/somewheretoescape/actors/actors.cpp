#include <t3d/t3dmodel.h>
#include "actors.hpp"
#include "./models/actor.hpp"
#include "../scene/time.hpp"

void Actors::updateActorsControls() {
    joypad_poll();

    _animated.updateAnimatedBodyControls(&_animated.escapePlayer1);
    _animated.updateAnimatedBodyControls(&_animated.escapePlayer2);
    _animated.updateAnimatedBodyControls(&_animated.escapePlayer3);
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

    float juriScale = 0.064f;

    _animated.escapePlayer1 = _animated.createAnimatedBody(ramModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[1],(T3DVec3){{0.0f, 0.0f, 0.0f}},  JOYPAD_PORT_1);
    _animated.escapePlayer2 = _animated.createAnimatedBody(squirModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[2],(T3DVec3){{0.0f, 0.0f, 0.0f}},  JOYPAD_PORT_2);
    _animated.escapePlayer3 = _animated.createAnimatedBody(bunnyModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[0],(T3DVec3){{0.0f, 0.0f, 0.0f}},  JOYPAD_PORT_3);

    actorBodys.push_back(
        _body.createActorBody(juriModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[7])
    );

    actorBodys.push_back(
        _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[8])
    );

    actorBodys.push_back(
        _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[6])
    );

}

void Actors::drawActors() {
    _animated.render(&_animated.escapePlayer1, _time.deltaTime);
    _animated.render(&_animated.escapePlayer2, _time.deltaTime);
    _animated.render(&_animated.escapePlayer3, _time.deltaTime);

    _animated.drawAnimatedBody(&_animated.escapePlayer1);
    _animated.drawAnimatedBody(&_animated.escapePlayer2);
    _animated.drawAnimatedBody(&_animated.escapePlayer3);

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
