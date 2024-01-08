#pragma once

#include "ofMain.h"

class Camera {
    public:
        ofVec3f position = ofVec3f(0.f, 4.f, 0.f);

        ofVec2f worldToScreen(const ofVec3f& w) const;
        ofVec3f screenToWorld(const ofVec2f& s) const;
        ofVec3f startRenderPosition() const;

        void setup();
        void draw();

    private:
        const ofVec3f kScale = ofVec3f(1.f, 1.f, 1.f);
        const float kCarWidth = 2.f;

        ofImage carImg;
};
