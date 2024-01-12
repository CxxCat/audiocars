#include "road_segment.h"

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

void RoadSegment::drawRect(const std::vector<ofVec3f>& coords, const ofColor& color, const Camera& camera) const {
    ofSetColor(color);
    ofBeginShape();
    for (int i = 0; i < coords.size(); ++i) {
        auto pos = camera.worldToScreen(coords[i]);
        ofVertex(pos.x, pos.y);
    }
    ofEndShape();
}
