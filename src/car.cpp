#include "car.h"

Car::Car(const Camera& camera, float topSpeedKmph, float acc100Kmph) {
    position = camera.startRenderPosition() + ofVec3f(0.f, 0.f, kOffset);
    topSpeed = kmphToMps(topSpeedKmph);
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

void Car::move(ofVec3f direction, float dt) {
    if (direction.z > 0) {
        speed += acceleration * dt;
    } else {
        direction.z *= -1;
        speed -= acceleration * dt;
    }
    speed = std::min(speed, topSpeed);
    speed = std::max(speed, 0.f);

    position += direction * speed * dt;
    position.x = std::min(position.x, kRangeX / 2.f);
    position.x = std::max(position.x, -kRangeX / 2.f);
}

float Car::speedKmph() const {
    return speed * 3600.f / 1000.f;  
}

float Car::kmphToMps(float kmph) const {
    return kmph * 1000.f / 3600.f;
}

