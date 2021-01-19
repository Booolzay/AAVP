#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


using namespace glm;

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

	// openFrameworks audio in and out fuunctions
	void audioOut(ofSoundBuffer& output) override; //output method
	void audioIn(ofSoundBuffer& input) override; //input method
	ofSoundStream soundStream;

	//Maximilian
	int bufferSize;
	int sampleRate;
	ofxMaxiSample sample;
	maxiMix mix;
	double audio;
	double outputs[2];
	float smoothedVolume = 0;
	float scaledVolume = 0;
	float decayRate = 0.05;
	float beats;
	float cubeat;

	//Sizing and spacing for tiles;
	int size = 60, squareSpacing = 50, squareDist;
	double b;

	//shader calls
	ofShader spotLight;
	ofShader beatTiles;

	//display triggers
	int showTiles, showSpotlight;
	
};
