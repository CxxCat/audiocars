#include "controller_input_generator.h"

ofVec3f ControllerInputGenerator::input() const {
    return ofVec3f(stearingWheelPos, 0.f, 0.f);
}

void ControllerInputGenerator::keyPressed(int key) {
    switch (key) {
        case OF_KEY_LEFT:
            stearingWheelPos -= 1.f;
            break;
        case OF_KEY_RIGHT:
            stearingWheelPos += 1.f;
            break;
    }
    stearingWheelPos = ofClamp(stearingWheelPos, -1.f, 1.f);
}

void ControllerInputGenerator::keyReleased(int key) {
    switch (key) {
        case OF_KEY_LEFT:
            stearingWheelPos += 1.f;
            break;
        case OF_KEY_RIGHT:
            stearingWheelPos -= 1.f;
            break;
    }
    stearingWheelPos = ofClamp(stearingWheelPos, -1.f, 1.f);
}
