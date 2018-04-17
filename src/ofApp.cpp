//
//  ofApp.cpp
//  example
//
//  Created by Pierre Proske on 12/04/17.
//
//

#include "ofApp.h"

void ofApp::setup(){
    ofBackground(255);
	ofSetVerticalSync(true);
    ofSetWindowTitle("SENSORY EMPIRE - Orbbec Astra Body Tracker");

	astra.setup();
   // astra.setLicenseString("<INSERT LICENSE KEY HERE>");

	astra.initDepthStream();
    astra.initBodyStream();

    setupSplashScreen();
}

void ofApp::update(){	
    if(bSetupFinished) astra.update();

    else {
        curtime = ofGetElapsedTimeMillis();
        if(curtime-prevtime > maxtime) {
            bSetupFinished = true;
        }
    }

}

void ofApp::draw(){
    if(bSetupFinished) {
        astra.drawDepth(0, 0,ofGetWidth(),ofGetHeight());

        if(astra.getNumBodies() > 0) {
            for(int i = 0; i < astra.getNumBodies();i++) {
                for(int j = 0; j < astra.getNumJoints(i);j++)
                {
                    ofDrawCircle(astra.getJointPosition(i,j),5);
                }
            }
        }
    } else {
        drawSplashScreen();
    }
}

void ofApp::keyPressed(int key) {

}

void ofApp::setupSplashScreen() {
    bSetupFinished = false;
    curtime = prevtime = ofGetElapsedTimeMillis();
    maxtime = 3000;
    string fn = "DINNeuzeitGroteskStd-Light.otf";
    font.load(fn,32,true);
    font2.load(fn,26,true);
}

void ofApp::drawSplashScreen() {
    const string title = "Astra Orbbec Body Tracker";
    const string s = "SENSORY";
    const string e = "EMPIRE";
    float sw = font.stringWidth(title);

    ofPushStyle();
    ofSetLineWidth(3);

    ofSetColor(80);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight()/2);

    ofSetColor(150);
    font.drawString(title,ofGetWidth()/2.0f - sw/2.0f,ofGetHeight()/2.0f - 100);

    ofSetColor(0);
    ofDrawLine(250,ofGetHeight()/2+50,ofGetWidth()-250,ofGetHeight()/2+50);
    sw = font2.stringWidth(s);
    font2.drawString(s,ofGetWidth()/2.0f - sw/2.0f,ofGetHeight()/2.0f+100);
    sw = font2.stringWidth(e);
    font2.drawString(e,ofGetWidth()/2.0f - sw/2.0f,ofGetHeight()/2.0f + font.stringHeight(s)+110);

    if(curtime-prevtime > 2500) {
        float f = ((curtime-prevtime + 1 - 2500)/500)*255.0f;
        ofSetColor(0,0,0,f);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    }
    ofPopStyle();
}
