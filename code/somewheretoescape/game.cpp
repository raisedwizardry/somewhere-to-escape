#include <t3d/t3d.h>
#include "game.hpp"

void SomewhereToEscapeGame::start() {
	setup();

	for (;;) {
		render();
	}

    cleanup();
}

void SomewhereToEscapeGame::updateControls() {
	_actors.updateActorsControls();
}

void SomewhereToEscapeGame::setup() {
	_lifecycle.initSetup();
	_scene.setupScene();

	_actors.createActors();

	_time.setupTime();
}

void SomewhereToEscapeGame::render() {
	// ======== Update ======== //
	_time.updateTime();
	updateControls();

	// ======== Draw (3D) ======== //
	_lifecycle.initDraw3d();
	_scene.updateScene();
	_scene.drawScene();

	_physics.stepSimulation(_time.deltaTime);
	//_physics.stepSimulation();

	_time.syncPoint = rspq_syncpoint_new();

	_actors.drawActors();

	// ======== Draw (UI) ======== //
	_lifecycle.drawUi();
}

void SomewhereToEscapeGame::cleanup() {
	t3d_destroy();
}
