#include <t3d/t3d.h>
#include "lifecycle.hpp"
#include <libdragon.h>
#include <GL/gl.h>
#include <GL/gl_integration.h>
#include <t3d/t3danim.h>


void Lifecycle::initSetup() {
    debug_init_isviewer();

    debug_init_usblog();

    asset_init_compression(2);

    timer_init();

    audio_init(32000, 3);

    mixer_init(32);

    dfs_init(DFS_DEFAULT_LOCATION);
    console_init();
    console_set_debug(1);

    display_close();
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);


    rdpq_init();
    //rdpq_debug_start();

    gl_init();

    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

    joypad_init();

    t3d_init((T3DInitParams){});
}

void Lifecycle::initDraw3d() {
    rdpq_attach(display_get(), display_get_zbuf());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    t3d_frame_start();

    rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
    t3d_screen_clear_color(RGBA32(100, 0, 100, 0));
    t3d_screen_clear_depth();
}

void Lifecycle::drawUi() {
    float posX = 8;
    float posX1 = 16;
    float posX2 = 24;
    float posX3 = 40;
    float posX4 = 56;
    float otherPosX = 32;
    float posY = 16;
    float otherPosY1 = 64;
    float otherPosY2 = 80;
    float otherPosY3 = 96;
    float otherPosY4 = 112;
    float otherPosY5 = 128;
    float otherPosY6 = 144;
    float otherPosY7 = 160;
    float otherPosY8 = 176;
    float otherPosY9 = 192;
    float otherPosY10 = 210;
    float otherPosY11 = 226;
    float otherPosY12 = 234;

    rdpq_sync_pipe();
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY1, "rX:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY1, std::to_string(_animated.escapePlayer1.rotation.x).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY2, "rY:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY2, std::to_string(_animated.escapePlayer1.rotation.y).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY3, "rZ:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY3, std::to_string(_animated.escapePlayer1.rotation.z).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY4, "pX:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY4, std::to_string(_animated.escapePlayer1.position.x).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY5, "pY:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY5, std::to_string(_animated.escapePlayer1.position.y).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY6, "pZ:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY6, std::to_string(_animated.escapePlayer1.position.z).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY7, "7:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY7, std::to_string(t3d_anim_get_time(&_animated.escapePlayer1.animKickCrescent)).c_str() );
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY8, "8:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY8, "Debug");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY9, "9:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY9, "Debug");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY10, "10:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY10, "Debug");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY11, "11:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY11, "Debug");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY12, "12:");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, otherPosX, otherPosY12, "Debug");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, posY, "FPS: %.2f", display_get_fps());

    rdpq_detach_show();
}