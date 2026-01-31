#include <t3d/t3d.h>
#include "game.hpp"
#include <libdragon.h>

void checkForSkip(void *ctx, int frame_idx, float time_sec, fmv_control_t *ctrl) {
	joypad_poll();
	joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

	if (btn.start) {
		ctrl->stop(ctrl);
	}
}

bool isStartGame() {
	joypad_poll();
	joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

	if (btn.start) {
		return true;
	}
	return false;
}

void SomewhereToEscapeGame::start() {
	video_register_codec(&mpeg1_codec);

	auto params = (fmv_parms_t){
		.disable_subtitles = true,
		.osd_callback = checkForSkip
	};
	fmv_play("rom://logo.m1v", &params);

	display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE);

	for (;;) {
		_menu.mainMenu();
		mixer_try_play();

		if (isStartGame()) {
			break;
		}
	}

	for (;;) {
		_menu.selectCharacter();
		mixer_try_play();

		if (isStartGame()) {
			break;
		}
	}

	setup();

	for (;;) {

		if (_action.isPaused) {
			_action.checkForUnpause();
		}
		else {
			render();
		}
		//exit the loop for quit functionality
	}

    cleanup();
}

void SomewhereToEscapeGame::updateControls() {
	joypad_poll();

	_scene.updateControls();

	_actors.updateActorsControls();

}

void SomewhereToEscapeGame::setup() {
	_scene.setupScene();

	_actors.createActors();

	_time.setupTime();
}

void SomewhereToEscapeGame::render() {
	// ======== Update ======== //
	_time.updateTime();
	updateControls();

	// ======== Draw (3D) ======== //
	mixer_try_play();

	_lifecycle.initDraw3d();

	_scene.updateScene();
	mixer_try_play();

	_scene.drawScene();

	_physics.stepSimulation();
	mixer_try_play();

	_actors.drawActors();
	mixer_try_play();

	_time.syncPoint = rspq_syncpoint_new();

	// ======== Draw (UI) ======== //
	_lifecycle.drawUi();
}

void SomewhereToEscapeGame::cleanup() {
	t3d_destroy();
}
