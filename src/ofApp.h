// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxOsc.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 12345


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    float x, y, nx, ny, xd1, xd2, yd1, yd2, ndiff;
    ofxFaceTracker2 tracker;
    ofVideoGrabber grabber;
    ofxOscSender sender;
    ofVideoPlayer video;
    
};

