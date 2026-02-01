#include "action.hpp"

void Action::checkForUnpause() {
    for (;;) {
        if (isUnpausePressed()) {
            isPaused = false;
            break;
        }
    }

}

bool Action::isUnpausePressed() {
    joypad_poll();
    joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if (btn.start) {
        return true;
    }
    return false;
}
