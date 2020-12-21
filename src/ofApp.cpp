#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    playback.update(currentMousePos);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // currentMouse
    ofSetColor(240, 120, 240);
    ofxDrawDirectionalCircle(currentMousePos, beforeMousePos, 10);
    
    // playbackMouse
    ofSetColor(120, 240, 240);
    
    auto currentPositions = playback.getCurrentPositions();
    
    for (int i = 0; i < beforePositions.size(); ++i) {
        ofxDrawDirectionalCircle(currentPositions[i], beforePositions[i], 10);
    }
    
    for (auto& p : playback.getCurrentPositions()) {
        ofDrawCircle(p, 10);
    }
    
    
    // progress bar
    auto status = playback.getCurrentStatus();
    if (status == PositionPlayback::PlaybackStatus::Recording) {
        ofSetColor(255, 0, 0);
    } else if (status == PositionPlayback::PlaybackStatus::StandbyRecord) {
        ofSetColor(255, 127, 127);
    } else {
        ofSetColor(255);
    }
    
    ofDrawRectangle(0, 0, ofGetWidth() * playback.getProgress(), 10);
    
    beforePositions = move(currentPositions);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {
        playback.startRecord();
    } else if (key == 'c') {
        playback.clearRecords();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    beforeMousePos = currentMousePos;
    currentMousePos = glm::vec2(x, y);
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
