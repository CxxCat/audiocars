#include "camera.h"

#include "ofMain.h"

ofVec2f Camera::worldToScreen(const ofVec3f& w) const {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth(); 

    ofVec2f ret;
    ret.y = (position.y + w.y) * kScale.z / (w.z - position.z) + kScale.y / 2;
    ret.y *= winHeight;

    ret.x = (position.x - w.x) * kScale.z / (w.z - position.z) + kScale.x / 2;
    ret.x *= winWidth; 
    return ret;
}

ofVec3f Camera::screenToWorld(const ofVec2f& s) const {
    const int winHeight = ofGetWindowHeight();

    ofVec3f ret;
    ret.z = position.y * kScale.z / (s.y / winHeight - kScale.y / 2) + position.z;
    return ret;
}

ofVec3f Camera::startRenderPosition() const {
    const int winHeight = ofGetWindowHeight();
    return screenToWorld(ofVec2f(0.f, winHeight));
}

void Camera::setup() {
    carImg.load("car0.png");
}

void Camera::draw() {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth(); 

    ofVec3f center = startRenderPosition();
    ofVec3f left = center - ofVec3f(0.f, kCarWidth / 2, 0.f);
    ofVec3f right = center + ofVec3f(0.f, kCarWidth / 2, 0.f);

    ofVec2f scrLeft = worldToScreen(left);
    ofVec2f scrRight = worldToScreen(right);

    float scrWidth = scrRight.y - scrLeft.y;
    float carScale = carImg.getWidth() / scrWidth;
    float scrHeight = carImg.getHeight() / carScale;

    carImg.resize(scrWidth, scrHeight);

    ofSetColor(ofColor::white);
    carImg.draw((winWidth - scrWidth) / 2, winHeight - scrHeight);
}
