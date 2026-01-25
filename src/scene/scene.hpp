#pragma once

#include "setting.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "action.hpp"
#include "sound.hpp"
#include "../utility/button.hpp"
#include "../debugmode.hpp"

#define TOTAL_PLAYERS 4

class Scene {
    public:
        Scene(Setting& setting, Lights& lights, Camera& camera, Action& action, Sound& sound, DebugMode& debug)
            : _setting(setting) , _lights(lights) , _camera(camera) , _action(action) , _sound(sound), _debug(debug) {
        }
        void setupScene();
        void updateControls();
        void updateScene();
        void drawScene();
        joypad_port_t currentPort = Button::ports[0];
    private:
        Setting& _setting;
        Lights& _lights;
        Camera& _camera;
        Action& _action;
        Sound& _sound;
        DebugMode& _debug;
};
