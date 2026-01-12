#pragma once
#include "../utility/button.hpp"

class Action {
    public:
        Action() {
        }
        void updateControls(joypad_inputs_t joypadInput);
        bool isPaused = false;
        void checkForUnpause();
    private:
        bool isPausedMode = false;
        bool isHoldingStart = false;
};
