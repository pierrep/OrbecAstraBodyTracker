
#pragma once

#include "ofMain.h"
#include "ofxOrbbecAstra.h"
#include "ofxOsc.h"

#ifdef TARGET_WIN32
#include "ofxSpout.h"
#endif

#ifdef TARGET_OSX
#include "ofxSyphon.h"
#endif

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
	void setupSpout();
    void setupSyphon();

	ofxOrbbecAstra astra;

    ofxOscSender oscSender;
    string hostname;
    int port;

    ofXml xml;

    bool bDrawBody;

    bool bSetupFinished;
    float curtime, prevtime, maxtime;
    ofTrueTypeFont font,font2;

#ifdef TARGET_WIN32
	/* Spout */
	ofxSpout::Sender spoutSender;
#endif

#ifdef TARGET_OSX
    ofxSyphonServer syphonServer;
#endif
    
};
