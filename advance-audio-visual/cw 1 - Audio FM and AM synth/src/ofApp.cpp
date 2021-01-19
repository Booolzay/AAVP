#include "ofApp.h"
//FM + AM Synthesis with Mouse interaction
//Frequency Modulation on Mousemovement on the X Axis
//Amplitude modulation on Mousemovement on teh Y Axis
//Please use headphones
//--------------------------------------------------------------
void ofApp::setup() {
	sampleRate = 44100;
	bufferSize = 512;
	ofBackground(0);
	frequency = 440;
	modspeed = 1;

	int sampleRate = 44100; /* Sampling Rate */
	int bufferSize = 512;

	ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

	// of Sound setup
	ofSoundStreamSettings settings;
	auto devices = soundStream.getMatchingDevices("default");

	if (!devices.empty()) {
		settings.setInDevice(devices[0]);
	}

	settings.setInListener(this);
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	//drawing visual instructions
	ofBeginShape();
	ofNoFill();
	ofSetColor(255);
	ofDrawBitmapString("FM",120, ofGetHeight() / 2 - 20);
	ofDrawBitmapString("X <-->", 120, ofGetHeight() / 2 + 20);
	ofVertex(120, ofGetHeight()/2);
	ofVertex(900, ofGetHeight() / 2);
	ofEndShape();

	ofBeginShape();

	ofDrawBitmapString("AM", ofGetWidth() / 2 - 30, 130);
	ofDrawBitmapString("Y ^ v", ofGetWidth() / 2 + 10, 130);
	ofVertex(ofGetWidth() / 2, 120);
	ofVertex(ofGetWidth() / 2, 640);
	ofEndShape();

	

}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output) {
	std::size_t nChannels = output.getNumChannels();
	for (std::size_t i = 0; i < output.getNumFrames(); i++) {
		currentSample = osc.sawn(frequency) * amplitude.sinewave(modspeed); //frequency ampped to mouseX, Amplitued mapped to mouseY

		output[i * nChannels] = currentSample;
		output[i * nChannels + 1] = currentSample;

		

	}
}

void ofApp::audioIn(ofSoundBuffer& input) {
	std::size_t nChannels = input.getNumChannels();
	for (std::size_t i = 0; i < input.getNumFrames(); ++i) {
		//handle input here
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	modspeed = ofMap(y, 0, ofGetHeight(), 0, 50);
	frequency = ofMap(x, 0, ofGetWidth(), 0, 880);
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
