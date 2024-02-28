#pragma once

#include <list>
#include <memory>
#include <vector>

#include "camera.h"
#include "spectrum.h"

class Car;

class NpcManager {
    public:
        NpcManager(const Spectrum& spectrum, Camera &camera);

        void setup();
        void update(float dt);
    private:
        const float kMaxDistance = 175.f;
        const float kGenDistance = 160.f;
        const float kTopSpeed = 130.f;
        const float kAcceleration = 4.2f;
        const float kCooldown = 1.f;
        const float kOffset = 3.f;
        const int kMaxVisibleCars = 10;

        Camera& camera;
        const Spectrum& spectrum;
        float cooldown = 0.f;

        std::list<shared_ptr<Car>> visibleCars;
        std::vector<shared_ptr<Car>> invisibleCars;

        std::string imagePath(int i) const;
};
