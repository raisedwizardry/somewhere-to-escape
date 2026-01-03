#include <t3d/t3d.h>
#include "scene.hpp"

void Scene::setupScene() {
    _camera.viewport = t3d_viewport_create();

    _lights.setupLighting();

    _setting.createSetting();
}

void Scene::updateScene() {
    _camera.updateCamera(&_camera.viewport);

    t3d_viewport_attach(&_camera.viewport);

    _lights.updateLighting();
}

void Scene::drawScene() {
    _setting.drawMap();
}
