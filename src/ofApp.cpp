#include "ofApp.h"

void sumInput(const ofVec3f& input, ofVec3f& ret) {
    if (input.x > 0) {
        ret.x = std::max(input.x, ret.x);
    } else if (input.x < 0) {
        ret.x = std::min(input.x, ret.x);
    }

    if (input.z > 0) {
        ret.z = std::max(input.z, ret.x);
    } else if (input.z < 0) {
        ret.z = std::min(input.z, ret.x);
    }
}

ofApp::ofApp(): car(new Car(camera, 293.f, 4.2f)), road(camera)
{}

//--------------------------------------------------------------
void ofApp::setup(){
    soundPlayer.load("music.mp3");
    soundPlayer.play();

    ttFont.load("arial.ttf", 32);

    road.setup();
    car->setup("car0.png");
    camera.drawByOrder.push_back(car);

    cameraOffset = car->position - camera.position;
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();

    soundPlayer.setVolume(static_cast<float>(!isMuted));

    ofVec3f input = ofVec3f::zero();
    sumInput(audioInputGenerator.input(), input);
    sumInput(controllerInputGenerator.input(), input);

    car->move(input, dt);
    camera.position = car->position - cameraOffset;

    //camera.screenTransform.x = sin(camera.position.z / 100.f);
    camera.screenTransform.y = cos(camera.position.z / 100.f) * 0.5f;

    road.update();
    camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor fromColor(231, 249, 245);
    ofColor toColor(221, 196, 252);

    ofBackgroundGradient(fromColor, toColor, OF_GRADIENT_BAR);

    camera.draw();
    int speedKmph = static_cast<int>(car->speedKmph());


    const int winHeight = ofGetWindowHeight();
    ofSetColor(ofColor::white);
    ttFont.drawString(std::to_string(speedKmph) + " km/h", 10, winHeight - 60);

    audioInputGenerator.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    controllerInputGenerator.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'm') {
        isMuted = !isMuted;
        return;
    }
    controllerInputGenerator.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
