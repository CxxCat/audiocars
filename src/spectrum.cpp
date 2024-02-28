#include "spectrum.h"

Spectrum::Spectrum()
    : cache(kBands) {
}


void Spectrum::update() {
    float* spectrum = ofSoundGetSpectrum(kBands);
    memcpy(cache.data(), spectrum, kBands * sizeof(float));
}

const std::vector<float>& Spectrum::get() const {
    return cache;
}
