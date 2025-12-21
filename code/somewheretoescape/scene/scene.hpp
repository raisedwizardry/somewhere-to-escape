#pragma once

#include "setting.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "action.hpp"

class Scene {
    public:
        Scene(Setting& setting, Lights& lights, Camera& camera, Action& action)
            : _setting(setting) , _lights(lights) , _camera(camera) , _action(action) {
        }
        void setupScene();
        void updateScene();
        void drawScene();
    private:
        Setting& _setting;
        Lights& _lights;
        Camera& _camera;
        Action& _action;
};
