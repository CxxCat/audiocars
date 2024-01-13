#include "ofApp.h"

ofApp::ofApp(): road(camera)
{}

//--------------------------------------------------------------
void ofApp::setup(){
    road.setup();
    camera.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.position += direction.getNormalized() * kSpeed * ofGetLastFrameTime();

    camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor fromColor(231, 249, 245);
    ofColor toColor(221, 196, 252);

    ofBackgroundGradient(fromColor, toColor, OF_GRADIENT_BAR);

    road.draw();
    camera.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            direction.z = 1.f;
            break;
        case OF_KEY_DOWN:
            direction.z = -1.f;
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
        case OF_KEY_DOWN:
            direction.z = 0.f;
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
