#pragma once

#include "camera.h"
#include "idrawable.h"
#include "ofMain.h"

class Tree: public IDrawable {
    public:
        ofVec3f position;

        Tree(const ofVec3f& center, int side, const ofImage& image);

        float order() override;
        void draw(const Camera& camera) override;

    private:
        const float kWidth = 8.f;
        const float kOffset = 20.f;
        const float kRange = 12.f;

        ofImage image;
        float width = kWidth;
};
