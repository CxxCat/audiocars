#include "car.h"

Car::Car(const Camera& camera, float topSpeedKmph, float acc100Kmph) {
    position = camera.startRenderPosition() + ofVec3f(0.f, 0.f, kOffset.z);
    topSpeed = kmphToMps(topSpeedKmph);
    minSpeed = kmphToMps(kMinSpeedKmph);
    acceleration = kmphToMps(100.f) / acc100Kmph;
}

void Car::setup(const std::string& imgPath) {
    image.load(imgPath);
}

float Car::order() {
    return position.z;
}

void Car::draw(const Camera& camera) {
    ofVec2f scrSize = camera.scaleByWidth(position, kWidth, image);

    ofVec2f scrPosition = camera.worldToScreen(position);
    ofSetColor(ofColor::white);
    image.draw(
        scrPosition.x - scrSize.x / 2,
        scrPosition.y - scrSize.y,
        scrSize.x,
        scrSize.y
    );
}

void Car::move(const ofVec3f& input, float dt) {
    speed += acceleration * input.z * dt;
    speed = ofClamp(speed, minSpeed, topSpeed);

    direction = ofVec3f::zero();
    direction.z = 1.f;
    if (input.x > 0.f) {
        direction.x = 1.f;
    } else if (input.x < 0.f) {
        direction.x = -1.f;
    }
    float invSpeedRate = 1.f - speedRate();
    direction.x *= (kMinTurnSensivity + (kMaxTurnSensivity - kMinTurnSensivity) * invSpeedRate);
    direction.normalize();

    position += direction * speed * dt;
    position.x = ofClamp(position.x, -kOffset.x, kOffset.x);
}

float Car::speedKmph() const {
    return speed * 3600.f / 1000.f;
}

float Car::speedRate() const {
    return speed / topSpeed;
}

float Car::kmphToMps(float kmph) const {
    return kmph * 1000.f / 3600.f;
}

