#include "npc_manager.h"

#include "car.h"
#include "ofMain.h"

NpcManager::NpcManager(const Spectrum& spectrum, Camera &camera)
    : spectrum(spectrum)
    , camera(camera) {
}

void NpcManager::setup() {
    for (int i = 1; i < 4; ++i) {
        invisibleCars.emplace_back(new Car(camera.startRenderPosition(), kTopSpeed, kAcceleration));
        invisibleCars.back()->setup(imagePath(i));
        camera.drawByOrder.push_back(invisibleCars.back());
    }
}

void NpcManager::update(float dt) {
    ofVec3f input(0.f, 0.f, 1.f);
    for (const auto& car : visibleCars) {
        car->move(input, dt); 
    }

    ofVec3f renderPos = camera.startRenderPosition();

    while (!visibleCars.empty() && visibleCars.front()->position.z < renderPos.z) {
        auto car = visibleCars.front();
        visibleCars.pop_front();
        invisibleCars.push_back(car);
        car->position = ofVec3f::zero();
    }

    while (!visibleCars.empty() && visibleCars.back()->position.z > renderPos.z + kMaxDistance) {
        auto car = visibleCars.back();
        visibleCars.pop_back();
        invisibleCars.push_back(car);
        car->position = ofVec3f::zero();
    }

    if (cooldown > 0.f) {
        cooldown -= dt;
        return;
    }

    if (visibleCars.size() > kMaxVisibleCars) {
        return;
    }

    const auto& spectr = spectrum.get();
    float sum = std::accumulate(spectr.begin(), spectr.begin() + 3, 0.f);
    if (sum < 3) {
        return;
    }

    std::shared_ptr<Car> car;
    ofVec3f pos = renderPos + ofVec3f(ofRandomf() * kOffset, 0.f, kGenDistance);
    if (invisibleCars.empty()) {
        car.reset(new Car(pos, kTopSpeed, kAcceleration));
        int imgIdx = static_cast<int>(ofRandom(1, 4));
        car->setup(imagePath(imgIdx));
        camera.drawByOrder.push_back(car);
    } else {
        car = invisibleCars.back();
        invisibleCars.pop_back();
        car->position = pos;
    }
    visibleCars.push_back(car);
    cooldown = kCooldown;
}

std::string NpcManager::imagePath(int i) const {
    return "car" + std::to_string(i) + ".png";
}
