#pragma once

#include <vector>

#include "ofMain.h"
#include "camera.h"

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

class Road {
    public:
        Road(Camera& camera);

        void setup();
        void draw();

    private:
        const int kSegments = 100;
        const float kTreeOffset = 8.f;

        Camera& camera;

        std::vector<ofColor> roadColors;
        std::vector<ofColor> grassColors;
        std::vector<std::shared_ptr<RoadSegment>> segments;

        std::vector<ofImage> treeImages;
        std::vector<std::shared_ptr<Tree>> trees;
};
