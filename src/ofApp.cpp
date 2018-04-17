
#include "ofApp.h"

void ofApp::setup(){
    ofBackground(255);
	ofSetVerticalSync(true);
    ofSetWindowTitle("SENSORY EMPIRE - Orbbec Astra Body Tracker");

	astra.setup();
   // astra.setLicenseString("<INSERT LICENSE KEY HERE>");

	astra.initDepthStream();
    astra.initBodyStream();
    astra.initHandStream();

    loadSettings();
    setupOsc();
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
        ofPushStyle();
        ofSetHexColor(0x179EFF);
        astra.drawDepth(0, 0,ofGetWidth(),ofGetHeight());
        ofPopStyle();

        if((astra.getNumBodies() > 0) && (bDrawBody)) {
            for(int i = 0; i < astra.getNumBodies();i++) {
                for(int j = 0; j < astra.getNumJoints(i);j++)
                {
                    ofDrawCircle(astra.getJointPosition(i,j),5);
                    ofDrawBitmapString(astra.getJointName(astra.getJointType(i,j)),astra.getJointPosition(i,j)+ofVec2f(10,0));
                    sendJointOsc(astra.getJointPosition(i,j),astra.getJointName(astra.getJointType(i,j)));
                }
            }
        }

        int hand_count = 0;
        for (auto& hand : astra.getHandsDepth()) {
            auto& pos = hand.second;
            sendJointOsc(ofVec2f(hand.second.x/ofGetWidth(),hand.second.y/ofGetHeight()),ofToString(hand_count++));
            ofPushStyle();
            ofSetColor(ofColor::red);
            ofDrawCircle(pos, 10);

            stringstream ss;
            ss << "id: " << hand.first << endl;
            ss << "pos: " << hand.second;
            ss << "count: " << hand_count-1;
            ofDrawBitmapStringHighlight(ss.str(), pos.x, pos.y - 30);
            ofPopStyle();
        }


    } else {
        drawSplashScreen();
    }
}

void ofApp::keyPressed(int key) {
    //if(key == 'b') bDrawBody = !bDrawBody;
}

void ofApp::loadSettings()
{
    bDrawBody = true;

    bool bOpen = xml.load("settings.xml");
    if(bOpen) {
        if(xml.exists("//HOSTNAME")) {
            hostname = xml.getValue<string>("//HOSTNAME");
        } else {
            hostname = "localhost";
        }
        if(xml.exists("//PORT")) {
            port = xml.getValue<int>("//PORT");
        } else {
            port = 66666;
        }

    } else {
        hostname = "localhost";
        port = 66666;
    }
}

void ofApp::setupOsc()
{
    ofLogNotice("BodyTracker") << "Setting hostname to " << hostname;
    oscSender.setup(hostname,port);
}

void ofApp::sendJointOsc(ofVec2f pos, string oscAddr)
{
    ofxOscMessage m;
    m.setAddress("/astra/"+oscAddr);
    m.addFloatArg(pos.x);
    m.addFloatArg(pos.y);
    oscSender.sendMessage(m, false);
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
