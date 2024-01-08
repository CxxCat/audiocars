#pragma once

#include "ofMain.h"

#include "camera.h"
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

        const ofVec3f kSpeedX = ofVec3f(1.f, 0.f, 0.f);
        const ofVec3f kSpeedY = ofVec3f(0.f, 1.f, 0.f);
        const ofVec3f kSpeedZ = ofVec3f(0.f, 0.f, 1.f);

        Camera camera;
        Road road;
};
