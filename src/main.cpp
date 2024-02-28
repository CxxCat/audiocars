#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
    settings.setGLVersion(3, 2); //we define the OpenGL version we want to use
	//settings.setSize(3840, 2160);
	//settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN
	settings.setSize(2048, 1536);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();
}
