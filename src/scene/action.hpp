#pragma once
#include "../utility/button.hpp"

class Action {
    public:
        Action() {
        }
        void checkForUnpause();
    private:
        bool isUnpausePressed();
};
