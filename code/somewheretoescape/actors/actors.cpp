#include <t3d/t3dmodel.h>
#include "actors.hpp"
#include "./models/actor.hpp"
#include "../scene/time.hpp"

void Actors::updateActorsControls() {
    joypad_poll();

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

    float juriScale = 0.064f;

    _animated.escapePlayer1 = _animated.createAnimatedBody(ramModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[1],(T3DVec3){{0.0f, 0.0f, 0.0f}},  JOYPAD_PORT_1);

    actorBodys.push_back(
        _body.createActorBody(juriModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[15])
    );
    actorBodys.push_back(
        _body.createActorBody(dwellerModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[8])
    );

    actorBodys.push_back(
        _body.createActorBody(bunnyModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[0])
    );

    actorBodys.push_back(
        _body.createActorBody(squirModel, (T3DVec3){{juriScale, juriScale, juriScale}}, blockPositions[2])
    );

}

void Actors::drawActors() {
    _animated.render(&_animated.escapePlayer1, _time.deltaTime);

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
