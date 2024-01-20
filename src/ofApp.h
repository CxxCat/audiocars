#pragma once

#include <memory>

#include "audio_input_generator.h"
#include "camera.h"
#include "car.h"
#include "controller_input_generator.h"
#include "ofMain.h"
#include "road.h"

class ofApp : public ofBaseApp{

	public:
        ofApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    private:
        const float kSpeed = 10.f;
        ofTrueTypeFont ttFont;

        ofVec3f cameraOffset = ofVec3f(0.f, 0.f, 0.f);

        Camera camera;
        std::shared_ptr<Car> car;
        Road road;

        ofSoundPlayer soundPlayer;
        bool isMuted = true;

        AudioInputGenerator audioInputGenerator;
        ControllerInputGenerator controllerInputGenerator;
};
