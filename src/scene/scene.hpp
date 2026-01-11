#pragma once

#include "setting.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "action.hpp"
#include "sound.hpp"

class Scene {
    public:
        Scene(Setting& setting, Lights& lights, Camera& camera, Action& action, Sound& sound)
            : _setting(setting) , _lights(lights) , _camera(camera) , _action(action), _sound(sound) {
        }
        void setupScene();
        void updateScene();
        void drawScene();
    private:
        Setting& _setting;
        Lights& _lights;
        Camera& _camera;
        Action& _action;
        Sound& _sound;
};
