#include "audio_input_generator.h"

#include <numeric>

AudioInputGenerator::AudioInputGenerator(const Spectrum& spectrum)
    : spectrum(spectrum)
    , fastEma(kEmaFastAlpha)
    , slowEma(kEmaSlowAlpha)
{}

ofVec3f AudioInputGenerator::input() {
    const auto& spectr = spectrum.get();

    float sum = std::accumulate(spectr.begin(), spectr.end(),  0.f);
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
