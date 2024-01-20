#include "camera.h"

#include <algorithm>

#include "idrawable.h"
#include "ofMain.h"

ofVec2f Camera::worldToScreen(const ofVec3f& w) const {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();

    ofVec2f ret;
    ret.y = (position.y - w.y) * scale.z * scale.y / (w.z - position.z);
    ret.x = (w.x - position.x) * scale.z * scale.x / (w.z - position.z);

    transform(ret);

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

void Camera::update() {
    const int winHeight = ofGetWindowHeight();
    const int winWidth = ofGetWindowWidth();

    scale.x = static_cast<float>(winHeight) / winWidth;

    std::sort(drawByOrder.begin(), drawByOrder.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs->order() > rhs->order();
    });
}

void Camera::draw() {
    for (const auto& iDraw : drawByOrder) {
        iDraw->draw(*this);
    }

}

float Camera::alpha(float order) const {
    if (drawByOrder.empty()) {
        return 1.f;
    }

    float len = drawByOrder.front()->order() - drawByOrder.back()->order();
    float ret = (drawByOrder.front()->order() - order) / len;
    return std::min(ret * kAlpha, 1.f);
}

void Camera::transform(ofVec2f& scrCoords) const {
    const float kPower = 5.f;
    const float kInvPower = 1 / kPower;
    if (scrCoords.y > 0) {
        ofVec2f shift;
        shift.x = 1.f / (scrCoords.y * 2.f * kPower + kInvPower) - kInvPower;
        shift.x = std::max(shift.x / (2.f * kPower), 0.f);
        scrCoords.x += shift.x * screenTransform.x;

        shift.y = 1.f / (scrCoords.y * 2.f * kPower + kInvPower) - kInvPower;
        shift.y = std::max(shift.y / (2.f * kPower), 0.f);
        scrCoords.y -= shift.y * screenTransform.y;
    }
}

