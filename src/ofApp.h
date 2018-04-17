//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOrbbecAstra.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);

    void setupSplashScreen();
    void drawSplashScreen();
    void sendJointOsc(ofVec2f pos, string oscAddr);
    void setupOsc();
    void loadSettings();

	ofxOrbbecAstra astra;

    ofxOscSender oscSender;
    string hostname;
    int port;

    ofXml xml;

    bool bDrawBody;

    bool bSetupFinished;
    float curtime, prevtime, maxtime;
    ofTrueTypeFont font,font2;

};
