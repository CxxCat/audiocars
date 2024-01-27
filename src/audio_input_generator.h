#pragma once

#include "ema.h"
#include "ofMain.h"
#include "spectrum.h"

class AudioInputGenerator {
    public:
        AudioInputGenerator(const Spectrum& spectrum);
        ofVec3f input();
    private:
        const float kEmaFastAlpha = 0.01f;
        const float kEmaSlowAlpha = 0.002f;

        const Spectrum& spectrum;
        EMA fastEma;
        EMA slowEma;
};
