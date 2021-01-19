#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//This sample needs to be a 16-bit .wav file
	firewood.load(ofToDataPath("firewood-beat.wav"));
	cdrkik.load(ofToDataPath("snare.wav"));
	kick1.load(ofToDataPath("kick04.wav"));
	kick2.load(ofToDataPath("blip.wav"));

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

	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofNoFill();
	ofSetColor(0);
	ofDrawBitmapString("a, s, d, f to trigger individual samples / A, S, D, F to Stop Individual Samples", 50, 50);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output) {
	std::size_t nChannels = output.getNumChannels();
	for (std::size_t i = 0; i < output.getNumFrames(); i++) {

		currentCount = (int)timer.phasor(8);//this sets up a metronome that ticks 8 times a second


		if (lastCount != currentCount) {//if we have a new timer int this sample, play the sound

			firewoodtrigger = hit[playHead % 16];//get the value out of the array for the firewood
			cdrkiktrigger = cdrkikhit[playHead % 16];
			kick1Trigger = kick1Hit[playHead % 16];
			kick2Trigger = kick2Hit[playHead % 16];//same for the cdrkik
			playHead++;//iterate the playhead
			lastCount = 0;//reset the metrotest
		}

		if (firewoodtrigger == 1 && t1 == 1) {//if the sequence has a 1 in it

			firewood.trigger();//reset the playback position of the sample to 0 (the beginning)

		}

		if (cdrkiktrigger == 1 && t2 == 1) {

			cdrkik.trigger();//likewise for the cdrkik

		}
		if (kick1Trigger == 1 && t3 == 1) {
			kick1.trigger();
		}
		if (kick2Trigger == 1 && t4 == 1) {
			kick2.trigger();
		}

		sampleOut = firewood.playOnce() + cdrkik.playOnce() + kick1.playOnce() + kick2.playOnce();//just play the file. No looping.

		output[i * nChannels] = sampleOut;
		output[i * nChannels + 1] = output[i * nChannels];
		firewoodtrigger = 0;//set trigger to 0 at the end of each sample to guarantee retriggering.
		cdrkiktrigger = 0;
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
	
	switch (key) {
	case 'a':
		t1 = 1;
		break;
	case 'A':
		t1 = 0;
		break;

	case 's':
		t2 = 1;
		break;
	case 'S':
		t2 = 0;
		break;

	case 'd':
		t3 = 1;
		break;
	case 'D':
		t3 = 0;
		break;

	case 'f':
		t4 = 1;
		break;
	case 'F':
		t4 = 0;
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

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
