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
            camera.position += kSpeedZ;
            break;
        case OF_KEY_DOWN:
            camera.position -= kSpeedZ;
            break;
        case OF_KEY_LEFT:
            camera.position -= kSpeedX;
            break;
        case OF_KEY_RIGHT:
            camera.position += kSpeedX;
            break;
        case 'a':
            camera.position += kSpeedY;
            break;
        case 'z':
            camera.position -= kSpeedY;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
