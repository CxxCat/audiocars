#include "road_segment.h"

RoadSegment::RoadSegment(int idx, const ofColor& fgColor, const ofColor& bgColor)
    : idx(idx)
    , positionZ(kSize.y * idx)
    , fgColor(fgColor)
    , bgColor(bgColor) {
}

float RoadSegment::order() {
    return positionZ + kSize.y;
}

void RoadSegment::draw(const Camera& camera) {
    const int winWidth = ofGetWindowWidth();
    const ofVec3f start = camera.startRenderPosition();
    const float beginZ = std::max(positionZ, start.z);
    const float endZ = positionZ + kSize.y;

    ofVec2f beginPos = camera.worldToScreen(ofVec3f(0.f, 0.f, beginZ));
    ofVec2f endPos = camera.worldToScreen(ofVec3f(0.f, 0.f, endZ));
    ofSetColor(bgColor);
    ofBeginShape();
    ofVertex(0, beginPos.y);
    ofVertex(winWidth, beginPos.y);
    ofVertex(winWidth, endPos.y);
    ofVertex(0, endPos.y);
    ofEndShape();

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
    drawRect(coords, fgColor, camera);

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
        drawRect(coords, fgColor, camera);
    }
}

void RoadSegment::drawRect(const std::vector<ofVec3f>& coords, const ofColor& fgColor, const Camera& camera) const {
    ofSetColor(fgColor);
    ofBeginShape();
    for (int i = 0; i < coords.size(); ++i) {
        auto pos = camera.worldToScreen(coords[i]);
        ofVertex(pos.x, pos.y);
    }
    ofEndShape();
}
