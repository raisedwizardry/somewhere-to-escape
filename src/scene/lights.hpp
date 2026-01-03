#pragma once
#include <t3d/t3d.h>

class Lights {
    public:
        void setupLighting();
        void updateLighting();
    private:
        T3DVec3 lightDirVec;
        uint8_t colorAmbient[4] = {0xAA, 0xAA, 0xAA, 0xFF};
        uint8_t colorDir[4] = {0xFF, 0xAA, 0xAA, 0xFF};
};
