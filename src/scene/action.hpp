#pragma once

#include "time.hpp"

class Action {
    public:
        Action(Time& time)
            : _time(time) {
        }
        void pause();
        void quietOnTheSet();
        void cut();
    private:
        Time& _time;
};
