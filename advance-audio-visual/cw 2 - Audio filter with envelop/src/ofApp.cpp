#include "ofApp.h"
//Use of Maximillian Envelope and Filter
//Press and Hold Space <- repeat
//Please use headphones is thers no Audio in Speakers
//Tried to change the audio stream setting to the Gitlab example version but was casuing problem with this project

//--------------------------------------------------------------
void ofApp::setup(){
	sampleRate = 44100;
	bufferSize = 512;
	frequency = 200;
	ofSoundStreamSetup(2, 0, this, sampleRate, bufferSize, 4);
	ofSetBackgroundColor(0);
	
	//Envelope setup
	env.setAttack(500);
	env.setDecay(10);
	env.setSustain(0.5);
	env.setRelease(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::audioOut(float *output, int bfferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		oscOutPut = env.adsr(1., env.trigger);//Envelop trigger setup
		int CurrentCount = osc3.phasor(1, 1, 9);

		if (trigger == 1) {
			if (CurrentCount == 1) env.trigger = 1;
		}
		else env.trigger = 0;

		sound = osc.sinewave(frequency);

		


		filteredOutput = filter.hires(sound, oscOutPut * 1000, 10); //filtering oscilator and envelope output with a hires filter
		output[i * nChannels] = filteredOutput;
		output[i * nChannels + 1] = filteredOutput;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		trigger = 1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ' ') {
		trigger = 0;
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
