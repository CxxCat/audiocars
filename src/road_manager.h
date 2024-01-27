#pragma once

#include <memory>

#include "ema.h"
#include "ofMain.h"
#include "spectrum.h"

class Car;

class RoadManager {
    public:
        RoadManager(const Spectrum& spectrum, const std::shared_ptr<Car>& car);
        void update(float dt);
        ofVec2f transform();
        ofVec3f input();
    private:
        enum class State {
            NoTurn,
            LeftTurn,
            RightTurn
        };

        const float kMinStateDistance = 500.f;
        const float kMaxStateDistance = 2000.f;

        const Spectrum& spectrum;
        std::shared_ptr<Car> car;
        
        EMA ema10;
        EMA ema100;
        EMA ema500;

        ofVec2f currTransform = ofVec2f(0.f, 0.f);
        ofVec2f targetTrasform = ofVec2f(0.f, 0.f);

        State state = State::NoTurn;
        float stateDistance = kMaxStateDistance;
        float prevCarZ = 0.f;

        void switchState(const std::vector<float>& spectr, float sum);
};
