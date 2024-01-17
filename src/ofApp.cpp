#include "ofApp.h"

ofApp::ofApp(): car(new Car(camera, 293.f, 4.2f)), road(camera)
{}

//--------------------------------------------------------------
void ofApp::setup(){
    ttFont.load("arial.ttf", 32);

    road.setup();
    car->setup("car0.png");
    camera.drawByOrder.push_back(car);

    cameraOffset = car->position - camera.position;
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    car->move(direction.getNormalized(), dt);
    camera.position = car->position - cameraOffset;

    camera.screenTransform.x = sin(camera.position.z / 100.f);
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

    ofSetColor(ofColor::white);
    ttFont.drawString(std::to_string(speedKmph), 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            direction.z = 1.f;
            break;
        case OF_KEY_LEFT:
            direction.x = -1.f;
            break;
        case OF_KEY_RIGHT:
            direction.x = 1.f;
            break;
        case 'a':
            direction.y = 1.f;
            break;
        case 'z':
            direction.y -= 1.f;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
            direction.z = -1.f;
            break;
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
            direction.x = 0.f;
            break;
        case 'a':
        case 'z':
            direction.y = 0.f;
            break;
    }
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
