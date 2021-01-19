#include "ofApp.h"
//Adapted from https://www.youtube.com/watch?v=vi2Ae2K1GQY i.e. added mouse interaction
//Move you mouse on the ofApp Window to see shader effect
//Texture ref : https://aminoapps.com/c/gintama/page/blog/gintama-funny-face-reaction/X0x7_b4ecguRp6rJDW51jgQw1l56njErYmK

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
	myShader.load("shader.vert", "shader.frag");
    gintoki.load("image.jpg");
    gintoki.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
 
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	myShader.begin();
	myShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	myShader.setUniform1f("mouseX", ofGetMouseX());
	myShader.setUniform1f("mouseY", ofGetMouseY());
	myShader.setUniformTexture("imageTexture", gintoki.getTexture(), 1);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	myShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
