#include "ofApp.h"

//Beat Detection code adapted from https://github.com/edap/examplesOfxMaxim
//Square tiles code adapted from https://www.openprocessing.org/sketch/695750
//Audio file source https://www.youtube.com/watch?v=4h4ZcmUme9I converted to wav for 16 bit support

//--------------------------------------------------------------

//INSTRUCTIONS: MOVE MOUSE AROUND THE ofApp WINDOW WHILE PRESSING DOWN "q" or "e" 

//--------------------------------------------------------------
void ofApp::setup() {

	spotLight.load("colorCircle"); //Loading shader for spot light
	beatTiles.load("shader"); //Loading my custom shader from small AAVP small Courseworks
	
	showSpotlight = 0; //Setting default view off for both modes by Deafult
	showTiles = 0;
	
	sample.load(ofToDataPath("weekend.wav")); 

	// of Sound setup-------------
	sampleRate = 44100; 
	bufferSize = 512;

	ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

	
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
	
	ofBackground(0);

	//-------------------
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	
	//initialising variables for spotlight shader use

	float windowWidth = ofGetWidth();
	float windowHeight = ofGetHeight();

	
	vec2 mousePos = vec2(mouseX, mouseY); //initialising mouseX and Y pos into mousePos

	
	float circleRadius = mousePos.x* beats * 2; // Calculate size of the circle that will just touch the sides of the display window
												 // Times Beat to be manipulated by sample beat
												 //Times 2 to make default radius of shader circle bigger
	if (mousePos.y < circleRadius) {
		circleRadius = mousePos.y * beats * 2;
	}

	if (windowWidth - mousePos.x < circleRadius) {
		circleRadius =  mousePos.x * beats * 2;
	}

	if (windowHeight - mousePos.y < circleRadius) {
		circleRadius = mousePos.y * beats * 2;
	}

	if (showSpotlight == 1) { //While "q"is Pressed Spotlight is activated
		
		spotLight.begin();
		spotLight.setUniform1f("windowWidth", windowWidth);
		spotLight.setUniform1f("windowHeight", windowHeight);
		spotLight.setUniform2f("mousePos", mousePos);
		spotLight.setUniform1f("circleRadius", circleRadius);


		for (int j = 20; j < ofGetWidth(); j += squareSpacing) {
			for (int i = 20; i < ofGetHeight(); i += squareSpacing) {
				ofNoFill();
				ofSetLineWidth(20);
				squareDist = sqrt(((mouseX - i) * (mouseX - i)) + ((mouseY - j) * (mouseY - j))) / 15; //Calculating mouse distance and to implement square inflation near mouse cursor
				cubeat = beats * 6;
				ofDrawRectangle(i, j, (cubeat * (sqrt(size - squareDist)) * (sqrt(size - squareDist))), (cubeat * (sqrt(size - squareDist)) * (sqrt(size - squareDist)))); //Drawing rectangle grid multiplied by beat for jumpy effect with the beat detection
			}
		}
		spotLight.end();
	}
	else if (showTiles == 1 ) { //While "e"is Pressed beatTiles is activated
		beatTiles.begin();
		beatTiles.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
		beatTiles.setUniform1f("mouseX", mousePos.x);
		beatTiles.setUniform1f("mouseY", mousePos.y);
		for (int j = 20; j < ofGetWidth(); j += squareSpacing) {
			for (int i = 20; i < ofGetHeight(); i += squareSpacing) {
				ofNoFill();
				ofSetLineWidth(20);
				squareDist = sqrt(((mouseX - i) * (mouseX - i)) + ((mouseY - j) * (mouseY - j))) / 15; //Calculating mouse distance and to implement square inflation near mouse cursor
				cubeat = beats * 10;
				ofDrawRectangle(i, j, (cubeat * (sqrt(size - squareDist)) * (sqrt(size - squareDist))), (cubeat * (sqrt(size - squareDist)) * (sqrt(size - squareDist))));
			}
		}
		beatTiles.end();
	}

}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output) {
	std::size_t nChannels = output.getNumChannels();
	for (std::size_t i = 0; i < output.getNumFrames(); i++) {
		float rms = 0.0; //initialising rms and numcount
		int numCounted = 0;
		
			audio = sample.play(); 
			mix.stereo(audio, outputs, 0.5); //mixing outputs frm bth channels
			output[i * nChannels] = outputs[0];
			output[i * nChannels + 1] = outputs[1];

			//rms calculation to smooth out the loudness of the beat output
			float left = outputs[0];
			float right = outputs[1];
			rms += left * left; 
			rms += right * right;
			numCounted += 2;
		

		rms /= (float)numCounted;
		rms = sqrt(rms);

		beats = ofLerp(beats, 0.035, decayRate); //onset detection
		if (rms > beats) {
			beats = rms;
		}
	}
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input) {
	std::size_t nChannels = input.getNumChannels();
	for (std::size_t i = 0; i < input.getNumFrames(); ++i) {
		//handle input here
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) //display keys, press and hold since key release turns display off
	{
	case 'q': //Displays spotlight effect
		showSpotlight = 1;
		break;
	case 'e': //displays disco d=tiles effect
		showTiles = 1;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key)
	{
	case 'q':
		showSpotlight = 0;
		break;
	case 'e':
		showTiles = 0;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
