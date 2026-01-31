#include "menu.hpp"
#include <libdragon.h>

void Menu::mainMenu() {
    rdpq_attach(display_get(), display_get_zbuf());
    _sound.switchSoundByTuneId(MENU, 0);
    auto textParams = (rdpq_textparms_t){
        .width = 320,
        .align = ALIGN_CENTER
    };
    rdpq_text_print(&textParams, 3, 0, 65, "Somewhere to Escape");
    rdpq_text_print(&textParams, 3, 0, 80, "by");
    rdpq_text_print(&textParams, 3, 0, 95, "raisedwizardry");

    rdpq_text_print(&textParams, 3, 0, 180, "Press Start");

    rdpq_detach_show();
}

void Menu::selectCharacter() {
    static display_context_t disp = 0;
    disp = display_get();
    _sound.switchSoundByTuneId(SELECTION, 0);
    graphics_fill_screen(disp, graphics_convert_color(RGBA32(100, 0, 200, 0)));
    graphics_draw_sprite_trans(disp, 0, 0, ramHead);
    graphics_draw_text(disp, 160, 60, "Ram");
    display_show(disp);
}
