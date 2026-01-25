#include <t3d/t3d.h>
#include "game.hpp"
#include <libdragon.h>

void SomewhereToEscapeGame::start() {
	sprite_t *mario = sprite_load("rom://ram-headshot-s.sprite");
	sprite_t *border = sprite_load("rom://border.sprite");

	for (;;) {
		static display_context_t disp = 0;
		disp = display_get();
		graphics_fill_screen(disp, graphics_convert_color(RGBA32(100, 0, 100, 0)));

		//graphics_draw_sprite(  );
		//graphics_draw_sprite_trans(disp, 20, 150, mario);
		//graphics_draw_sprite_trans(disp, 150, 150, mario);
		graphics_draw_sprite_trans(disp, 20, 150, border);
		display_show(disp);

		joypad_poll();
		joypad_port_t port = JOYPAD_PORT_1;
		joypad_inputs_t joypadInput = joypad_get_inputs(port);
		auto buttonPress = Button::PriorityButtonQuery(joypadInput.btn);
		if (buttonPress == Button::BUTTON_A) {
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
