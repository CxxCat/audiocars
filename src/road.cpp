#include "road.h"

#include <string>

#include "ofMain.h"

RoadSegment::RoadSegment(int idx, const ofColor& color)
    : idx(idx)
    , positionZ(kSize.y * idx)
    , color(color) {
}

float RoadSegment::order() {
    return positionZ + kSize.y / 2;
}

void RoadSegment::draw(const Camera& camera) {
    const ofVec3f start = camera.startRenderPosition();
    const float beginZ = std::max(positionZ, start.z);
    const float endZ = positionZ + kSize.y;

    std::vector<ofVec3f> coords(4);
    float roadWidth = kSize.x + kLinesWidth;
    coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
    coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
    coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
    coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
    drawRect(coords, ofColor::white, camera);

    roadWidth = kSize.x;
    coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
    coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
    coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
    coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
    drawRect(coords, color, camera);

    if (idx % 2 == 1) {
        roadWidth = kSize.x / 3 + kLinesWidth / 2;
        coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
        coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
        coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
        coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
        drawRect(coords, ofColor::white, camera);

        roadWidth = kSize.x / 3 - kLinesWidth / 2;
        coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
        coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
        coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
        coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
        drawRect(coords, color, camera);
    }
}

Tree::Tree(const ofVec3f position, const ofImage& image)
    : position(position)
    , image(image) {
}

float Tree::order() {
    return position.z;
}

void Tree::draw(const Camera& camera) {
    ofVec2f scrSize = camera.scaleByWidth(position, kWidth, image);

    auto scrPosition = camera.worldToScreen(position);
    ofSetColor(ofColor::white);
    image.draw(
        scrPosition.x - scrSize.x / 2,
        scrPosition.y - scrSize.y,
        scrSize.x,
        scrSize.y
    );
}

void RoadSegment::drawRect(const std::vector<ofVec3f>& coords, const ofColor& color, const Camera& camera) const {
    ofSetColor(color);
    ofBeginShape();
    for (int i = 0; i < coords.size(); ++i) {
        auto pos = camera.worldToScreen(coords[i]);
        ofVertex(pos.x, pos.y);
    }
    ofEndShape();
}

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

