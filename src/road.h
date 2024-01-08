#pragma once

#include <vector>

#include "ofMain.h"
#include "camera.h"

class Road {
    public:
        Road(const Camera& camera);

        void draw();

    private:
        const int kSegments = 100;
        const ofVec2f kSegmentSize = ofVec2f(9.f, 3.f);

        std::vector<float> segments;
        std::vector<ofColor> roadColors;
        std::vector<ofColor> sandColors;

        const Camera& camera;

        void drawRect(const std::vector<ofVec3f>& coords, const ofColor& color) const;
};
