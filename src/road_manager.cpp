#include "road_manager.h"

#include <numeric>

#include "car.h"


RoadManager::RoadManager(const Spectrum& spectrum, const std::shared_ptr<Car>& car)
    : spectrum(spectrum)
    , car(car)
    , ema10(0.1)
    , ema100(0.01)
    , ema500(0.002)
    , prevCarZ(car->position.z){
}

void RoadManager::update(float dt) {
    const auto& spectr = spectrum.get();
    float sum = std::accumulate(spectr.begin(), spectr.end(), 0.f);
    float value = ema100.add(sum);
    float base = ema500.add(sum);

    switchState(spectr, sum);
    switch (state) {
        case State::NoTurn:
            targetTrasform.x = 0.f;
            break;
        case State::LeftTurn:
            targetTrasform.x = -1.f;
            break;
        case State::RightTurn:
            targetTrasform.x = 1.f;
            break;
    };

     
    float y = ofClamp(ema10.add(base - value), -0.5f, 0.5f);
    targetTrasform.y = abs(y) < 0.5f ? 0 : y;

    ofVec2f direction = targetTrasform - currTransform;
    direction.normalize();
    direction *= car->speedRate() * dt;

    if (direction.lengthSquared() > targetTrasform.squareDistance(currTransform)) {
        currTransform = targetTrasform;
        return;
    }

    currTransform += direction;
}

ofVec2f RoadManager::transform() {
    return currTransform;
}

ofVec3f RoadManager::input() {
    ofVec3f ret = ofVec3f::zero();
    ret.x = -0.5f * currTransform.x;
    return ret;
}

void RoadManager::switchState(const std::vector<float>& spectr, float sum) {
    stateDistance -= (car->position.z - prevCarZ);
    prevCarZ = car->position.z;
    if (stateDistance > 0.f) {
        return;
    }

    float normSum = 0;
    switch (state) {
        case State::LeftTurn:
        case State::RightTurn:
            state = State::NoTurn;
            normSum = std::min(sum, static_cast<float>(spectr.size())) / spectr.size();
            break;
        case State::NoTurn:
            float leftSum = 0.f;
            float rightSum = 0.f;
            for (int i = 0; i < spectr.size(); ++i) {
                if (i % 2 == 0) {
                    leftSum += spectr[i];
                } else {
                    rightSum += spectr[i];
                }
            }
            if (leftSum > rightSum) {
                state = State::LeftTurn;
                sum = leftSum;
            } else {
                state = State::RightTurn;
                sum = rightSum;
            }
            float halfSpectrSize = spectr.size() / 2;
            normSum = std::min(sum, halfSpectrSize) / halfSpectrSize;
            break;
    }
    stateDistance = kMinStateDistance + normSum * (kMaxStateDistance - kMinStateDistance);
}
