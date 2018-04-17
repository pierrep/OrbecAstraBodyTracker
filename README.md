# Orbbec Astra Body Tracker

Sends Body and hand tracking via OSC.

Set the port and host details via the settings.xml file.

Make sure to wave each hand in a circle until it connects if you want the separate hand tracking.


## OSC implementation

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

