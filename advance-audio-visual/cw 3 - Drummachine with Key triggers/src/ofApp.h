#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// openFrameworks audio stuff
	void audioOut(ofSoundBuffer& output) override; //output method
	void audioIn(ofSoundBuffer& input) override; //input method
	ofSoundStream soundStream;

	//Maximilian
	maxiSample firewood, cdrkik, kick1, kick2;
	maxiOsc timer; //and a timer

	int currentCount, lastCount, playHead, hit[16] = { 1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1 }; //This is the sequence for the firewood
	int cdrkikhit[16] = { 0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0 };
	int kick1Hit[16] = { 0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0 };//This is the sequence for the cdrkik
	int kick2Hit[16] = { 0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0 };

	int firewoodtrigger, cdrkiktrigger, kick1Trigger, kick2Trigger;

	double sampleOut;
	int t1, t2, t3, t4;

};
