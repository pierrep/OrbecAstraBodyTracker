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

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);

    void setupSplashScreen();
    void drawSplashScreen();

	ofxOrbbecAstra astra;

    bool bSetupFinished;
    float curtime, prevtime, maxtime;
    ofTrueTypeFont font,font2;

};
