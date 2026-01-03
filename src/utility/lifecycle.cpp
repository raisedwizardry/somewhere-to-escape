#include <t3d/t3d.h>
#include "lifecycle.hpp"

void Lifecycle::initSetup() {
    debug_init_isviewer();



    debug_init_usblog();
    asset_init_compression(2);

    timer_init();
    audio_init(32000, 3);
    mixer_init(32);

    dfs_init(DFS_DEFAULT_LOCATION);

    display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
    // console_init();
    // console_set_render_mode(RENDER_MANUAL);
    // console_set_debug(1);

    rdpq_init();
    //rdpq_debug_start();

    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

    joypad_init();
    t3d_init((T3DInitParams){});
}

void Lifecycle::initDraw3d() {
    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();

    rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
    t3d_screen_clear_color(RGBA32(100, 0, 100, 0));
    t3d_screen_clear_depth();
}

void Lifecycle::drawUi() {
    float posX = 16;
    float posY = 216;
    float otherPosY = 200;

    rdpq_sync_pipe();
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, posY, "Debug: --");
    rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, posX, otherPosY, "FPS: %.2f", display_get_fps());

    rdpq_detach_show();
}