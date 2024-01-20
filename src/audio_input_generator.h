#pragma once

#include "ofMain.h"

class AudioInputGenerator {
    public:
        ofVec3f input();
        void draw() const;
    private:
        const int kBands = 128;
        
        const ofColor kColor = ofColor(255, 255, 255, 200);
        const float kHeightPct = 0.8f;

        const float kEmaAlpha = 0.01f;

        float* spectrum = nullptr;
        float ema = 0.f;
};
