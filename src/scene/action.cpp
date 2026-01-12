#include "action.hpp"

void Action::checkForUnpause() {
    joypad_poll();
    for (size_t i = 0; i < 4; i++) {
        joypad_port_t port = Button::ports[i];
        joypad_inputs_t joypadInput = joypad_get_inputs(port);
        if (joypadInput.btn.start && isPaused) {
            isPaused = false;
        }
    }
}

void Action::updateControls(joypad_inputs_t joypadInput) {
    if (!isPaused) {
        if (joypadInput.btn.start && joypadInput.btn.b) {
            isPausedMode = false;
            isHoldingStart = false;
        }
        if (joypadInput.btn.start && isPausedMode && !isHoldingStart) {
            isHoldingStart = true;
        }
        else if (joypadInput.btn.start && !isPausedMode && !isHoldingStart) {
            isPausedMode = true;
        }

        if (isPausedMode && isHoldingStart) {
            isPaused = true;
        }
    }
}
