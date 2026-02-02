#include "sound.hpp"

#include <wav64.h>

void Sound::switchSoundByTuneId(Tune tune, int channel) {
    if (currenlyPlayingTune == tune && mixer_ch_playing(channel)) {
        return;
    }
    wav64_close(&currentTune);
    auto tuneFilename = getFilenameByTuneId(tune);
    wav64_open(&currentTune, tuneFilename);
    currenlyPlayingTune = tune;
    wav64_set_loop(&currentTune, true);
    mixer_ch_set_freq(channel, 44100);
    wav64_play(&currentTune, channel);
}

const char *Sound::getFilenameByTuneId(Tune tune) {
    switch (tune) {
        case MENU:
            return "rom:/menu.wav64";
        case INTRO:
            return "rom:/intro.wav64";
        case SELECTION:
            return "rom:/selection.wav64";
        case RUNAWAY:
            return "rom:/runaway.wav64";
        case MARCH:
            return "rom:/march.wav64";
        case JURI:
            return "rom:/fight-juri.wav64";
        case OUTRO:
            return "rom:/outro.wav64";
        default:
            return "rom:/logo.wav64";
    }
}
