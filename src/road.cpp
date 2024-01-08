#include "road.h"

#include "ofMain.h"

Road::Road(const Camera& camera): camera(camera), segments(kSegments) {
    for (int i = 0; i < kSegments; ++i) {
        segments[i] = (kSegments - 1 - i) * kSegmentSize.y;
    }
    roadColors.emplace_back(156, 158, 155);
    roadColors.emplace_back(144, 152, 147);

    sandColors.emplace_back(235, 213, 198);
    sandColors.emplace_back(243, 222, 202);
}

void Road::draw() {
    const int winWidth = ofGetWindowWidth();

    int segmentIdx = 0; 
    ofVec3f start = camera.startRenderPosition();

    for (auto& segment : segments) {

        float beginZ = std::max(segment, start.z);
        float endZ = segment + kSegmentSize.y;

        if (endZ > start.z) {
            ofVec2f beginPos = camera.worldToScreen(ofVec3f(0.f, 0.f, beginZ)); 
            ofVec2f endPos = camera.worldToScreen(ofVec3f(0.f, 0.f, endZ));
            
            ofSetColor(sandColors[segmentIdx]);
            ofBeginShape();
            ofVertex(0, beginPos.y);
            ofVertex(winWidth, beginPos.y);
            ofVertex(winWidth, endPos.y);
            ofVertex(0, endPos.y);
            ofEndShape();

            std::vector<ofVec3f> coords(4);
            const float linesWidth = 0.6f;

            float roadWidth = kSegmentSize.x + linesWidth;
            coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
            coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
            coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
            coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
            drawRect(coords, ofColor::white);

            roadWidth = kSegmentSize.x;
            coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
            coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
            coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
            coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
            drawRect(coords, roadColors[segmentIdx]);

            if (segmentIdx % 2 == 1) {
                roadWidth = kSegmentSize.x / 3 + linesWidth / 2;
                coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
                coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
                coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
                coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
                drawRect(coords, ofColor::white);

                roadWidth = kSegmentSize.x / 3 - linesWidth / 2;
                coords[0] = ofVec3f(-roadWidth / 2, 0.f, beginZ);
                coords[1] = ofVec3f(-roadWidth / 2, 0.f, endZ);
                coords[2] = ofVec3f(roadWidth / 2, 0.f, endZ);
                coords[3] = ofVec3f(roadWidth / 2, 0.f, beginZ);
                drawRect(coords, roadColors[segmentIdx]);
            }
        } else {
            segment += kSegments * kSegmentSize.y;    
        }

        ++segmentIdx;
        segmentIdx %= roadColors.size();
    }
}

void Road::drawRect(const std::vector<ofVec3f>& coords, const ofColor& color) const {
    ofSetColor(color);
    ofBeginShape();
    for (int i = 0; i < coords.size(); ++i) {
        auto pos = camera.worldToScreen(coords[i]);
        ofVertex(pos.x, pos.y);
    }
    ofEndShape();
}
