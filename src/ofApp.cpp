#include "ofApp.h"

void sumInput(const ofVec3f& input, ofVec3f& ret) {
    ret.x += input.x;
    ret.x = ofClamp(ret.x, -1.f, 1.f);

    if (input.z > 0) {
        ret.z = std::max(input.z, ret.x);
    } else if (input.z < 0) {
        ret.z = std::min(input.z, ret.x);
    }
}

ofApp::ofApp()
    : car(new Car(camera.startRenderPosition(), 293.f, 4.2f))
    , road(camera)
    , background(spectrum)
    , audioInputGenerator(spectrum)
    , roadManager(spectrum, car)
    , npcManager(spectrum, camera){
}

//--------------------------------------------------------------
void ofApp::setup(){
    soundPlayer.load("music.mp3");
    soundPlayer.play();

    ttFont.load("arial.ttf", 32);

    road.setup();
    background.setup();
    npcManager.setup();
    car->setup("car0.png");
    camera.drawByOrder.push_back(car);

    cameraOffset = car->position - camera.position;
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();

    soundPlayer.setVolume(static_cast<float>(!isMuted));
    spectrum.update();

    roadManager.update(dt);
    npcManager.update(dt);
    road.update();

    ofVec3f input = ofVec3f::zero();
    sumInput(audioInputGenerator.input(), input);
    sumInput(controllerInputGenerator.input(), input);
    sumInput(roadManager.input(), input);

    car->move(input, dt);
    camera.position = car->position - cameraOffset;

    ofVec2f screenTransform = roadManager.transform();
    camera.screenTransform = screenTransform;
    camera.update();
    background.screenTransform = screenTransform;
    background.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
    background.draw();
    camera.draw();
    int speedKmph = static_cast<int>(car->speedKmph());

    const int winHeight = ofGetWindowHeight();
    ofSetColor(ofColor::white);
    ttFont.drawString(std::to_string(speedKmph) + " km/h", 10, winHeight - 60);
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
