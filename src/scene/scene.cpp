#include <t3d/t3d.h>
#include "scene.hpp"

void Scene::setupScene() {
    _camera.viewport = t3d_viewport_create();

    _lights.setupLighting();

    _setting.createSetting();

    _camera.initCamera();

    _sound.setupSounds();
}

void Scene::updateControls() {
    for (size_t i = 0; i < TOTAL_PLAYERS; i++) {
        joypad_port_t port = Button::ports[i];
        currentPort = port;
        joypad_inputs_t joypadInput = joypad_get_inputs(port);
        _action.updateControls(joypadInput);

        if (currentPort == JOYPAD_PORT_4 && _debug.P4_CAMERA_DEBUG) {
            _camera.updateControls(joypadInput);
        }
    }

}

void Scene::updateScene() {
    _camera.renderCamera();

    t3d_viewport_attach(&_camera.viewport);

    _lights.updateLighting();
}

void Scene::drawScene() {
    _setting.drawMap();
}
