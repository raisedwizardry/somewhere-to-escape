#include "menu.hpp"
#include <libdragon.h>

void Menu::mainMenu() {
    rdpq_attach(display_get(), display_get_zbuf());
    _sound.switchSoundByTuneId(MENU, 0);

    rdpq_set_mode_fill(RGBA32(100, 0, 200, 0));
    rdpq_fill_rectangle(0, 0, 320, 240);
    auto textParams = (rdpq_textparms_t){
        .width = 320,
        .align = ALIGN_CENTER,
        .char_spacing = 2
    };
    rdpq_text_print(&textParams, 3, 0, 65, "Somewhere to Escape");
    rdpq_text_print(&textParams, 3, 0, 80, "by");
    rdpq_text_print(&textParams, 3, 0, 95, "raisedwizardry");

    rdpq_text_print(&textParams, 3, 0, 180, "Press Start");

    rdpq_detach_show();
}

void Menu::makeCharacterSelection() {
    disp = display_get();
    graphics_fill_screen(disp, graphics_convert_color(RGBA32(100, 0, 200, 0)));

    _sound.switchSoundByTuneId(MENU, 0);

    if (!isCharacterSelectionMade) {
        selectCharacter();
        checkPressButtonA();
    }
    else {
        confirmSelectedCharacter();
        checkPressButtonStart();
    }

    display_show(disp);
}


void Menu::selectCharacter() {
    getCharacterTextBySelectionId(currentSelectedCharacter);
    getCharacterSpriteBySelectionId(currentSelectedCharacter);
    graphics_draw_text(disp, 90, 20, "Press A to Select");
    // if (isPressButtonA()) {
    //     return true;
    // }
    // return false;
}

void Menu::getCharacterTextBySelectionId(Selection selection) {
    switch (selection) {
        case RAM:
            graphics_draw_text(disp, 150, 40, "Ram");
            break;
        case BUNNY:
            graphics_draw_text(disp, 137, 40, "Bunny");
            break;
        case SQUIR:
            graphics_draw_text(disp, 138, 40, "Squir");
            break;
        case NO_SELECTION:
        default:
            break;
    }
}

void Menu::getCharacterSpriteBySelectionId(Selection selection) {
    switch (selection) {
        case RAM:
            graphics_draw_sprite_trans(disp, 0, 0, ramHeadArrows);
            break;
        case BUNNY:
            graphics_draw_sprite_trans(disp, 0, 0, bunnyHeadArrows);
            break;
        case SQUIR:
            graphics_draw_sprite_trans(disp, 0, 0, squirHeadArrows);
            break;
        case NO_SELECTION:
        default:
            break;
    }
}

void Menu::getCharacterSelectedSpriteBySelectionId(Selection selection) {
    switch (selection) {
        case RAM:
            graphics_draw_sprite_trans(disp, 0, 0, ramHead);
            break;
        case BUNNY:
            graphics_draw_sprite_trans(disp, 0, 0, bunnyHead);
            break;
        case SQUIR:
            graphics_draw_sprite_trans(disp, 0, 0, squirHead);
            break;
        case NO_SELECTION:
        default:
            break;
    }
}

void Menu::confirmSelectedCharacter() {
    graphics_draw_text(disp, 80, 20, "Press Start to Confirm");
    getCharacterSelectedSpriteBySelectionId(currentSelectedCharacter);
}


void Menu::checkPressButtonA() {
    joypad_poll();
    joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if (btn.a) {
        isCharacterSelectionMade = true;
    }
}

void Menu::checkPressButtonStart() {
    joypad_poll();
    joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if (btn.start) {
        isCharacterSelectionConfirmed = true;
    }
}