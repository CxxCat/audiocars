#include "spectrum.h"

#include <map>
#include <numeric>

static std::map<int, int> gBars = {
    {0,   1  }, // Bass
    {1,   3  }, // Lower Midrange
    {3,   5  }, // Middle Midrange
    {5,   10 }, // Upper Midrange
    {10,  30 }, // Lower Treble
    {30,  50 }, // Middle Treble
    {50,  100}, // Upper Treble 
    {100, 200}  // Top octave >=10kHz
};

Spectrum::Spectrum()
    : cache(kBands)
    , vizBars(gBars.size()) {
}


void Spectrum::update() {
    float* spectrum = ofSoundGetSpectrum(kBands);
    memcpy(cache.data(), spectrum, kBands * sizeof(float));

    for (int i = 0; i < vizBars.size(); ++i) {
        vizBars[i] *= kAttenuation;
    }
}

const std::vector<float>& Spectrum::get() const {
    return cache;
}

void Spectrum::draw() {
    const int winWidth = ofGetWindowWidth();
    const int winHeight = ofGetWindowHeight();

    const float height = static_cast<float>(winHeight) / 2.f;
    const float width = static_cast<float>(winWidth) / (gBars.size() * 2);

    ofSetColor(kColor);
    int i = 0;
    for (auto bar = gBars.begin(); bar != gBars.end(); ++bar) {
        auto begin = cache.begin() + bar->first;
        auto end = cache.begin() + bar->second;
        float band = std::accumulate(begin, end, 0.f) / (bar->second - bar->first);
        vizBars[i] = std::max(vizBars[i], height * band);
        ofDrawRectangle(width * i, height, width * kSizePct, -vizBars[i]);
        ofDrawRectangle(winWidth - width * (i + 1), height, width * kSizePct, -vizBars[i]);
        ++i;
    }
}
