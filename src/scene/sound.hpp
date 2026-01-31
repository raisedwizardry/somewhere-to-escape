#pragma once
#include <t3d/t3d.h>

enum Tune {
    MENU,
    INTRO,
    SELECTION,
    RUNAWAY,
    MARCH,
    JURI
};

class Sound {
public:
    void switchSoundByTuneId(Tune tune, int channel);

private:
    wav64_t currentTune;
    Tune currenlyPlayingTune;
    static const char *getFilenameByTuneId(Tune tune);

};
