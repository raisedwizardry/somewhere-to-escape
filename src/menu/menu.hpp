#pragma once

#include "../scene/sound.hpp"
#include "../actors/models/selection.hpp"

class Menu {
    public:
        Menu(Sound& sound) : _sound(sound) {
        }
        void mainMenu();
        void makeCharacterSelection();
        void levelOneObjective();
        void levelThreeObjective();
        void levelTwoObjective();
        void gameComplete();
        Selection currentSelectedCharacter = NO_SELECTION;
        bool isCharacterSelectionMade = false;
        bool isCharacterSelectionConfirmed = false;
    private:
        void selectCharacter();
        void confirmSelectedCharacter();
        void checkButtonC();
        void checkPressButtonStart();
        display_context_t disp = 0;
        void getCharacterTextBySelectionId(Selection selection);
        void getCharacterSpriteBySelectionId(Selection selection);
        void getCharacterSelectedSpriteBySelectionId(Selection selection);

        sprite_t *ramHead = sprite_load("rom://select-ram.sprite");
        sprite_t *ramHeadArrows = sprite_load("rom://select-ram-arrows.sprite");
        sprite_t *bunnyHead = sprite_load("rom://select-bunny.sprite");
        sprite_t *bunnyHeadArrows = sprite_load("rom://select-bunny-arrows.sprite");
        sprite_t *squirHead = sprite_load("rom://select-squir.sprite");
        sprite_t *squirHeadArrows = sprite_load("rom://select-squir-arrows.sprite");

        Sound& _sound;
};
