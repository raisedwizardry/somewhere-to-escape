#pragma once

#include "../scene/sound.hpp"

class Menu {
    public:
        Menu(Sound& sound) : _sound(sound) {
        }
        void mainMenu();
        void selectCharacter();
    private:
        Sound& _sound;
        sprite_t *ramHead = sprite_load("rom://select-ram.sprite");
        sprite_t *bunnyHead = sprite_load("rom://select-bunny.sprite");
        sprite_t *squirHead = sprite_load("rom://select-ram.sprite");
};
