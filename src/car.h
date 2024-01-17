#pragma once

#include <string>

#include "camera.h"
#include "idrawable.h"
#include "ofMain.h"

class Car: public IDrawable {
    public:
        ofVec3f position;

        Car(const Camera& camera, float topSpeedKmph, float acc100Kmph);

        void setup(const std::string& imgPath);

        float order() override;
        void draw(const Camera& camera) override;

        void move(ofVec3f direction, float dt);
        float speedKmph() const;

    private:
        const float kWidth = 2.f;
        const float kOffset = 0.5f;
        const float kRangeX = 10.f;

        ofImage image;
        float topSpeed = 0.f;
        float acceleration = 0.f;
        float speed = 0.f;

        float kmphToMps(float kmph) const;
};

