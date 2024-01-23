#pragma once

#include "ema.h"
#include "ofMain.h"

class AudioInputGenerator {
    public:
        AudioInputGenerator();
        ofVec3f input();
        void draw() const;
    private:
        const int kBands = 200;
        
        const ofColor kColor = ofColor(255, 255, 255, 200);
        const float kHeightPct = 0.8f;

        const float kEmaFastAlpha = 0.01f;
        const float kEmaSlowAlpha = 0.002f;

        float* spectrum = nullptr;

        EMA fastEma;
        EMA slowEma;
};
