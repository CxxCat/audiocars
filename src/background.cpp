#include "background.h"

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

Background::Background(const Spectrum& spectrum)
    : spectrum(spectrum)
    , vizBars(gBars.size())
    , frontBars(gBars.size() * 2)
    , backBars(gBars.size() * 2) {
}

void Background::setup() {
    shader.load("background");

    const ofVec2f barSize = barMaxSize();
    for (int i = 0; i < gBars.size() * 2; ++i) {
        frontBars[i].x = barSize.x * i;
        backBars[i].x = barSize.x * i;
    } 
}

void Background::update(float dt) {
    const int winWidth = ofGetWindowWidth();
    
    const auto& spectr = spectrum.get();
    int vb = 0;
    for (auto bar = gBars.begin(); bar != gBars.end(); ++bar) {
        auto begin = spectr.begin() + bar->first;
        auto end = spectr.begin() + bar->second;
        vizBars[vb] = std::accumulate(begin, end, 0.f) / (bar->second - bar->first);
        ++vb;
    }

    float speed = dt * winWidth * (-screenTransform.x);
    updateBars(speed * kMaxFrontSpeed, kFrontAttenuation, frontBars);
    updateBars(speed * kMaxBackSpeed, kBackAttenuation, backBars);
}

void Background::updateBars(float speed, float attenuation, vector<ofVec2f>& bars) {
    const int winWidth = ofGetWindowWidth();
    const ofVec2f barSize = barMaxSize();
    for (int i = 0; i < bars.size(); ++i) {
        bars[i].y *= attenuation;
        int vb = i;
        if (i >= gBars.size()) {
            vb = gBars.size() - (i % gBars.size()) - 1;
        }
        bars[i].y = std::max(bars[i].y, barSize.y * vizBars[vb]);

        bars[i].x += speed;
        if (bars[i].x + barSize.x < 0) {
            bars[i].x += winWidth;
        }
        if (bars[i].x >= winWidth) {
            bars[i].x -= winWidth;
        }
    }
}

void Background::draw() {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();
    const ofVec2f barSize = barMaxSize(); 

    ofBackground(kSkyColor);

    ofSetColor(kBackColor);
    for (const auto& bar : backBars) {
        ofDrawRectangle(bar.x, winHeight / 2, barSize.x * kBackSizePct, -bar.y);
    }
    ofSetColor(kHorizonColor);
    for (const auto& bar : frontBars) {
        ofDrawRectangle(bar.x, winHeight / 2, barSize.x * kFrontSizePct, -bar.y);
    }

    shader.begin();
    shader.setUniform1f("winHeight", winHeight);
    ofFloatColor color = kHorizonColor;
    float color4f[] = {color.r, color.g, color.b, color.a};
    shader.setUniform4fv("globalColor", color4f);
    ofDrawRectangle(0, 0, winWidth, winHeight);
    shader.end();
}

ofVec2f Background::barMaxSize() const {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();
    return ofVec2f(
        static_cast<float>(winWidth) / (gBars.size() * 2), 
        static_cast<float>(winHeight) / 4.f);
}

