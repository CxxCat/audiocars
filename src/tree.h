#pragma once

#include "camera.h"
#include "idrawable.h"
#include "ofMain.h"

class Tree: public IDrawable {
    public:
        ofVec3f position;

        Tree(const ofVec3f position, const ofImage& image);

        float order() override;
        void draw(const Camera& camera) override;

    private:
        const float kWidth = 8.f;

        ofImage image;
};
