#include <t3d/t3d.h>
#include "scene.hpp"

void Scene::setupScene() {
    _camera.viewport = t3d_viewport_create();

    _lights.setupLighting();

    _setting.createSetting();

    _camera.initCamera();
}

void Scene::updateControls() {
    for (size_t i = 0; i < TOTAL_PLAYERS; i++) {
        joypad_port_t port = Button::ports[i];
        currentPort = port;
        joypad_inputs_t joypadInput = joypad_get_inputs(port);

        if (currentPort == JOYPAD_PORT_4 && _debug.P4_CAMERA_DEBUG) {
            _camera.updateControls(joypadInput);
        }
    }

}

void Scene::updateScene(GameState gameState) {
    if (gameState == LEVEL_1) {
        _sound.switchSoundByTuneId(RUNAWAY, 0);
    }
    else if (gameState == LEVEL_2) {
        _sound.switchSoundByTuneId(MARCH, 0);
    }
    else if (gameState == LEVEL_3) {
        _sound.switchSoundByTuneId(JURI, 0);
    }

    _camera.renderCamera();

    t3d_viewport_attach(&_camera.viewport);

    _lights.updateLighting();
    _setting.drawMap(gameState);
}
