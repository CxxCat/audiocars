#include "camera.h"

#include <algorithm>

#include "ofMain.h"

ofVec2f Camera::worldToScreen(const ofVec3f& w) const {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();

    ofVec2f ret;
    ret.y = (position.y + w.y) * scale.z * scale.y / (w.z - position.z);
    ret.x = (w.x - position.x) * scale.z * scale.x / (w.z - position.z);

    ret += ofVec2f(0.5f, 0.5f);
    ret.y *= winHeight;
    ret.x *= winWidth;
    return ret;
}

ofVec3f Camera::screenToWorld(const ofVec2f& s) const {
    const int winHeight = ofGetWindowHeight();

    ofVec3f ret;
    ret.z = position.y * scale.z / (s.y / winHeight - scale.y / 2) + position.z;
    return ret;
}

ofVec3f Camera::startRenderPosition() const {
    const int winHeight = ofGetWindowHeight();
    return screenToWorld(ofVec2f(0.f, winHeight));
}

ofVec2f Camera::scaleByWidth(const ofVec3f& center, float width, const ofImage& image) const {
    ofVec3f left = center - ofVec3f(width / 2, 0.f, 0.f);
    ofVec3f right = center + ofVec3f(width / 2, 0.f, 0.f);

    ofVec2f scrLeft = worldToScreen(left);
    ofVec2f scrRight = worldToScreen(right);

    float scrWidth = scrRight.x - scrLeft.x;
    float scale = image.getWidth() / scrWidth;
    float scrHeight = image.getHeight() / scale;

    return ofVec2f(scrWidth, scrHeight);
}

void Camera::setup() {
    carImg.load("car0.png");
}

void Camera::update() {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();

    scale.x = static_cast<float>(winHeight) / winWidth;
}

void Camera::draw() {
    std::sort(drawByOrder.begin(), drawByOrder.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs->order() > rhs->order();
    });

    for (const auto& iDraw : drawByOrder) {
        iDraw->draw(*this);
    }

    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();

    ofVec3f center = startRenderPosition() + ofVec3f(0.f, 0.f, 0.5f);
    ofVec2f scrSize = scaleByWidth(center, kCarWidth, carImg);

    ofVec2f scrCenter = worldToScreen(center);
    ofSetColor(ofColor::white);
    carImg.draw(
        scrCenter.x - scrSize.x / 2,
        scrCenter.y - scrSize.y,
        scrSize.x,
        scrSize.y
    );
}
