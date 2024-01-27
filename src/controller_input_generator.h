#pragma once

#include "ofMain.h"

class ControllerInputGenerator {
    public:
        ofVec3f input() const;
        void keyPressed(int key);
        void keyReleased(int key);
    private:
         float steeringWheelPos = 0.f;
};
