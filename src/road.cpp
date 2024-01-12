#include "road.h"

Road::Road(Camera& camera): camera(camera), treeImages(4) {
    roadColors.emplace_back(66, 81, 82);
    roadColors.emplace_back(41, 65, 66);

    grassColors.emplace_back(66, 105, 33);
    grassColors.emplace_back(99, 138, 57);

    for (int i = 0; i < kSegments; ++i) {
        ofColor color = roadColors[i % roadColors.size()];
        auto segment = std::make_shared<RoadSegment>(i, color);
        segments.push_back(segment);
        camera.drawByOrder.push_back(segment);
    }
}

void Road::setup() {
    for (int i = 0; i < treeImages.size(); ++i) {
        treeImages[i].load("tree" + std::to_string(i) + ".png");
    }

    for (int i = 0; i < segments.size(); ++i) {
        ofVec3f treePosition(kTreeOffset, 0.f, segments[i]->positionZ);
        auto tree = std::make_shared<Tree>(treePosition, treeImages[i % treeImages.size()]);
        trees.push_back(tree);
        camera.drawByOrder.push_back(tree);

        treePosition.x *= -1;
        tree = std::make_shared<Tree>(treePosition, treeImages[i % treeImages.size()]);
        trees.push_back(tree);
        camera.drawByOrder.push_back(tree);
    }
}

void Road::draw() {
    const int winWidth = ofGetWindowWidth();

    ofVec3f start = camera.startRenderPosition();

    for (int i = 0; i < segments.size(); ++i) {
        float beginZ = std::max(segments[i]->positionZ, start.z);
        float endZ = segments[i]->positionZ + segments[i]->kSize.y;

        if (endZ > start.z) {
            ofVec2f beginPos = camera.worldToScreen(ofVec3f(0.f, 0.f, beginZ));
            ofVec2f endPos = camera.worldToScreen(ofVec3f(0.f, 0.f, endZ));

            ofSetColor(grassColors[i % grassColors.size()]);
            ofBeginShape();
            ofVertex(0, beginPos.y);
            ofVertex(winWidth, beginPos.y);
            ofVertex(winWidth, endPos.y);
            ofVertex(0, endPos.y);
            ofEndShape();
        } else {
            const float roadLen = kSegments * segments[i]->kSize.y;
            segments[i]->positionZ += roadLen;
            trees[i * 2]->position.z += roadLen;
            trees[i * 2 + 1]->position.z += roadLen;
        }
    }
}

