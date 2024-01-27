#pragma once

#include <vector>

#include "camera.h"
#include "ofMain.h"
#include "road_segment.h"
#include "tree.h"

class Road {
    public:
        Road(Camera& camera);

        void setup();
        void update();

    private:
        const int kSegments = 88;

        Camera& camera;

        std::vector<ofColor> roadColors;
        std::vector<ofColor> grassColors;
        std::vector<std::shared_ptr<RoadSegment>> segments;

        std::vector<ofImage> treeImages;
        std::vector<std::shared_ptr<Tree>> trees;
};
