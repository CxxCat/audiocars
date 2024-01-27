#pragma once

#include <string>

#include "camera.h"
#include "idrawable.h"
#include "ofMain.h"

class Car: public IDrawable {
    public:
        const float kMinTurnSensivity = 0.1f;
        const float kMaxTurnSensivity = 0.3f;

        ofVec3f position;

        Car(const Camera& camera, float topSpeedKmph, float acc100Kmph);

        void setup(const std::string& imgPath);

        float order() override;
        void draw(const Camera& camera) override;

        void move(const ofVec3f& input, float dt);

        float speedKmph() const;
        float speedRate() const;

    private:
        const float kWidth = 2.f;
        const ofVec3f kOffset = ofVec3f(5.f, 0.f, 0.5f);
        const float kMinSpeedKmph = 40.f;


        ofImage image;
        float topSpeed = 0.f;
        float minSpeed = 0.f;
        float acceleration = 0.f;
        float speed = 0.f;
        ofVec3f direction = ofVec3f(0.f, 0.f, 0.f);

        float kmphToMps(float kmph) const;
};

