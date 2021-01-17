#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    //ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    
    // Setup grabber
    grabber.setup(1280,720);
    video.load("circle_loop.mov");
    video.play();
   
    
    // Setup tracker
    tracker.setup();
    x = 0;
    y = 0;
    xd1 = 0;
    yd1 = 0;
    xd2 = 0;
    yd2 = 0;
    
    
    // Open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    video.update();
    
    // Update tracker when there are new frames
    if(grabber.isFrameNew()){
        tracker.update(grabber);
    }
    
    //Get coordinates
    for (int i = 0; i< tracker.getInstances().size(); i++){
        x = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::NOSE_BASE).getCentroid2D().x;
        y = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::NOSE_BASE).getCentroid2D().y;
        xd1 = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_JAW).getCentroid2D().x;
        xd2 = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_JAW).getCentroid2D().x;
    }
    
    //Normalization of coordinates
    nx = ofMap(x, 0, grabber.getWidth(), 0.f, 1.f, true);
    ny = ofMap(y, 0, grabber.getHeight(), 0.f, 1.f, true);
    ndiff = ofMap((xd2 -xd1)* 5.f, 0, grabber.getWidth(), 0.f, 1.f, true);
    
   
    
    // x-axis
    ofxOscMessage mx;
    mx.setAddress("/head/positionx");
    mx.addFloatArg(nx);
    sender.sendMessage(mx, false);
    
    // y-axis
    ofxOscMessage my;
    my.setAddress("/head/positiony");
    my.addFloatArg(ny);
    sender.sendMessage(my, false);
    
    // z-axis ordered on wish
    ofxOscMessage mdiff;
    mdiff.setAddress("/head/position/diff");
    mdiff.addFloatArg(ndiff);
    sender.sendMessage(mdiff, false);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw video
    video.draw(0, 0, ofGetWidth(), ofGetHeight());
    // Draw circle
    ofDrawCircle((1-nx)*grabber.getWidth(), y, (1-ndiff)*100 + 10);
   
    
    // Draw text UI
    string buf = "sending osc messages to port: " + ofToString(PORT);
    buf += "\nmove head to left, right, up or down";
    buf += "\nPosition x: " + ofToString(x, 3);
    buf += "\nPosition y: " + ofToString(y, 3);
    ofDrawBitmapStringHighlight(buf, 10, 10);
    ofDrawBitmapStringHighlight("Framerate : "+ ofToString(ofGetFrameRate()) + "\n", 10, 65);
    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ ofToString(tracker.getThreadFps())+ "\n", 10, 80);
   
    
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    ofSetColor(ofColor::white);
#endif
}

