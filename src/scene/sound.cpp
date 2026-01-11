#include "sound.hpp"

#include <wav64.h>

void Sound::setupSounds() {
    wav64_open(&fightJuri, "rom:/fight-juri.wav64");
    wav64_set_loop(&fightJuri, true);
    mixer_ch_set_freq(0, 32000);

    wav64_play(&fightJuri, 0);
}
