#include "audio_input_generator.h"

AudioInputGenerator::AudioInputGenerator()
    : fastEma(kEmaFastAlpha)
    , slowEma(kEmaSlowAlpha)
{}

ofVec3f AudioInputGenerator::input() {
    spectrum = ofSoundGetSpectrum(kBands);
    float sum = 0.f;
    for (int i = 0; i < kBands; ++i) {
        sum += *(spectrum + i);
    }
    fastEma.add(sum);
    slowEma.add(sum);

    ofVec3f ret;
    if (fastEma.get() > slowEma.get()) {
        ret.z = 1.f;
    } else if (fastEma.get() < slowEma.get()) {
        ret.z = -1.f;
    }

    return ret;
}

void AudioInputGenerator::draw() const {
    if (spectrum == nullptr) {
        return;
    }

    const int winWidth = ofGetWindowWidth();
    const int winHeight = ofGetWindowHeight();

    const float height = static_cast<float>(winHeight) * 2.f / kBands;
    const float width = winWidth / 2.f;

    ofSetColor(kColor);
    int band10Khz = kBands / 2 - 1;
    for (int i = 0; i < band10Khz; ++i) {
        float band = *(spectrum + i);
        ofDrawRectangle(0, height * i, width * band, height * kHeightPct); 
        ofDrawRectangle(winWidth, height * i, -width * band, height * kHeightPct); 
    } 
    
    float sum = 0.f;
    for (int i = band10Khz; i < kBands; ++i) {
        sum += *(spectrum + i);
    }
    ofDrawRectangle(0, height * band10Khz, width * sum, height * kHeightPct); 
    ofDrawRectangle(winWidth, height * band10Khz, -width * sum, height * kHeightPct); 
}
