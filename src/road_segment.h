#pragma once

#include <vector>

#include "camera.h"
#include "idrawable.h"
#include "ofMain.h"

class RoadSegment: public IDrawable {
    public:
        const ofVec2f kSize = ofVec2f(9.f, 3.f);

        float positionZ = 0.f;

        RoadSegment(int idx, const ofColor& color);
        float order() override;
        void draw(const Camera& camera) override;

    private:
        const float kLinesWidth = 0.6f;

        int idx = 0;
        ofColor color;

        void drawRect(const std::vector<ofVec3f>& coords, const ofColor& color, const Camera& camera) const;
};
