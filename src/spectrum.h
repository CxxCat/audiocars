#pragma once

#include <vector>

#include "ofMain.h"

class Spectrum {
    public:
        Spectrum();

        void update();
        const std::vector<float>& get() const;
        void draw();
    private:
        const int kBands = 200;
        const ofColor kColor = ofColor(231, 249, 245, 200);
        const float kSizePct = 0.8f;
        const float kAttenuation = 0.98f;

        std::vector<float> cache;
        std::vector<float> vizBars;
};
