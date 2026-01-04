#pragma once
namespace Button {

    enum Button {
        BUTTON_A,   ///< @brief A button
        BUTTON_B,   ///< @brief B button
        BUTTON_Z,   ///< @brief Z button
        BUTTON_START,   ///< @brief Start button
        BUTTON_D_UP,   ///< @brief D-Pad Up
        BUTTON_D_DOWN,   ///< @brief D-Pad Down
        BUTTON_D_LEFT,   ///< @brief D-Pad Left
        BUTTON_D_RIGHT,   ///< @brief D-Pad Right
        BUTTON_L,  ///< @brief L trigger
        BUTTON_R,  ///< @brief R trigger
        BUTTON_C_UP,  ///< @brief C-Up button
        BUTTON_C_DOWN,  ///< @brief C-Down button
        BUTTON_C_LEFT,  ///< @brief C-Left button
        BUTTON_C_RIGHT,  ///< @brief C-Right button
        BUTTON_NOPRESS,  ///< @brief No Button pressed
    };

    inline Button PriorityButtonQuery(joypad_buttons_t input) {
        if (input.a) {
            return BUTTON_A;
        }
        if (input.b) {
            return BUTTON_B;
        }
        if (input.c_up) {
            return BUTTON_C_UP;
        }
        if (input.c_left) {
            return BUTTON_C_LEFT;
        }
        if (input.c_down) {
            return BUTTON_C_DOWN;
        }
        if (input.c_right) {
            return BUTTON_C_RIGHT;
        }
        if (input.z) {
            return BUTTON_Z;
        }
        if (input.l) {
            return BUTTON_L;
        }
        if (input.r) {
            return BUTTON_R;
        }
        if (input.d_up) {
            return BUTTON_D_UP;
        }
        if (input.d_left) {
            return BUTTON_D_LEFT;
        }
        if (input.d_down) {
            return BUTTON_D_DOWN;
        }
        if (input.d_right) {
            return BUTTON_D_RIGHT;
        }
        return BUTTON_NOPRESS;
    }
}
