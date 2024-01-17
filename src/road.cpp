#include "road.h"

Road::Road(Camera& camera): camera(camera), treeImages(4) {
    roadColors.emplace_back(66, 81, 82);
    roadColors.emplace_back(41, 65, 66);

    grassColors.emplace_back(66, 105, 33);
    grassColors.emplace_back(99, 138, 57);

}

void Road::setup() {
    for (int i = 0; i < treeImages.size(); ++i) {
        treeImages[i].load("tree" + std::to_string(i) + ".png");
    }

    for (int i = 0; i < kSegments; ++i) {
        int colorID = i / 2;
        ofColor fgColor = roadColors[colorID % roadColors.size()];
        ofColor bgColor = grassColors[colorID % grassColors.size()];
        auto segment = std::make_shared<RoadSegment>(i, fgColor, bgColor);
        segments.push_back(segment);
        camera.drawByOrder.push_back(segment);

        ofVec3f position(0.f, 0.f, segments[i]->positionZ);
        int side = i % 2 == 0 ? -1 : 1;
        auto tree = std::make_shared<Tree>(position, side, treeImages[i % treeImages.size()]);
        trees.push_back(tree);
        camera.drawByOrder.push_back(tree);
    }
}

void Road::update() {
    ofVec3f start = camera.startRenderPosition();

    for (int i = 0; i < segments.size(); ++i) {
        float beginZ = std::max(segments[i]->positionZ, start.z);
        float endZ = segments[i]->positionZ + segments[i]->kSize.y;

        if (endZ <= start.z) {
            const float roadLen = kSegments * segments[i]->kSize.y;
            segments[i]->positionZ += roadLen;
            trees[i]->position.z += roadLen;
        }
    }
}

