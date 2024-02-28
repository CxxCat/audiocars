#pragma once

#include <vector>

#include "ofMain.h"

class Spectrum {
    public:
        Spectrum();

        void update();
        const std::vector<float>& get() const;
    private:
        const int kBands = 200;

        std::vector<float> cache;
};
