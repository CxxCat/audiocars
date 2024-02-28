#pragma once

#include <vector>

#include "ofMain.h"
#include "spectrum.h"

class Background {
    public:
        ofVec2f screenTransform;

        Background(const Spectrum& spectrum);

        void setup();
        void update(float dt);
        void draw();
    private:
        ofColor kBackColor = ofColor(172, 111, 248);
        ofColor kHorizonColor = ofColor(231, 249, 245);
        ofColor kSkyColor = ofColor(221, 196, 252);

        const float kFrontAttenuation = 0.98f;
        const float kMaxFrontSpeed = 0.1f;
        const float kFrontSizePct = 0.8f;

        const float kBackAttenuation = 0.97f;
        const float kMaxBackSpeed = 0.05f;
        const float kBackSizePct = 0.9f;

        const Spectrum& spectrum;
        std::vector<float> vizBars;
        std::vector<ofVec2f> frontBars;
        std::vector<ofVec2f> backBars;

        ofShader shader;

        void updateBars(float speed, float attenuation, vector<ofVec2f>& bars);
        ofVec2f barMaxSize() const;
};
