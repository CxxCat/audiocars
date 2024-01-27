#include "controller_input_generator.h"

ofVec3f ControllerInputGenerator::input() const {
    return ofVec3f(steeringWheelPos, 0.f, 0.f);
}

void ControllerInputGenerator::keyPressed(int key) {
    switch (key) {
        case OF_KEY_LEFT:
            steeringWheelPos -= 1.f;
            break;
        case OF_KEY_RIGHT:
            steeringWheelPos += 1.f;
            break;
    }
    steeringWheelPos = ofClamp(steeringWheelPos, -1.f, 1.f);
}

void ControllerInputGenerator::keyReleased(int key) {
    switch (key) {
        case OF_KEY_LEFT:
            steeringWheelPos += 1.f;
            break;
        case OF_KEY_RIGHT:
            steeringWheelPos -= 1.f;
            break;
    }
    steeringWheelPos = ofClamp(steeringWheelPos, -1.f, 1.f);
}
