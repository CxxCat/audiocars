#pragma once

#include <memory>
#include <vector>

#include "ofMain.h"

class IDrawable;

class Camera {
    public:
        ofVec3f position = ofVec3f(0.f, 4.f, 0.f);
        std::vector<std::shared_ptr<IDrawable>> drawByOrder;

        ofVec2f worldToScreen(const ofVec3f& w) const;
        ofVec3f screenToWorld(const ofVec2f& s) const;
        ofVec3f startRenderPosition() const;
        ofVec2f scaleByWidth(const ofVec3f& center, float width, const ofImage& image) const;

        void setup();
        void update();
        void draw();

    private:
        const float kCarWidth = 2.f;

        ofVec3f scale = ofVec3f(1.f, 1.f, 1.f);
        ofImage carImg;

};
