#pragma once
#include "../utility/button.hpp"

class Action {
    public:
        Action() {
        }
        bool isPaused = false;
        void checkForUnpause();
    private:
        bool isUnpausePressed();
};
