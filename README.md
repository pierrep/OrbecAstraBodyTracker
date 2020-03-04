# Orbbec Astra Body Tracker

Sends Body and hand tracking via OSC.

On Windows, sends the depth image via Spout. The MacOS version send the depth image via Syphon.

Set the port and host details via the settings.xml file.

Make sure to wave each hand in a circle until it connects if you want the separate hand tracking.

## Building from source

The following addons are needed when building from source:
- Linux (none, no Spout or Syphon support)
- Windows: Spout https://github.com/elliotwoods/ofxSpout
- Mac OS: Syphon https://github.com/astellato/ofxSyphon

## OSC implementation
The OSC port is 66666 by default and is defined in the settings.xml in the data folder of the compiled app.

Body tracking osc messages:

    /astra/XXXX <float> <float>

where XXXX is one of the names below

    Head
    ShoulderSpine
    LeftShoulder
    LeftElbow
    LeftHand
    RightShoulder
    RightElbow
    RightHand
    MidSpine
    BaseSpine
    LeftHip
    LeftKnee
    LeftFoot
    RightHip
    RightKnee
    RightFoot
    LeftWrist
    RightWrist
    Neck

Hand Tracking osc messages:

    /astra/0 <float> <float>
    /astra/1 <float> <float>

