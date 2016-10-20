//
//  ofApp.cpp
//  example
//
//  Created by Matt Felsen on 11/15/15.
//
//

#include "ofApp.h"

void ofApp::setup(){
    
	ofBackground(0);
	ofSetWindowShape(640*2, 480 * 2);
	ofSetVerticalSync(true);


	bUseRegistration = false;

	astra1.setup("device/sensor0");
	astra1.enableRegistration(bUseRegistration);
	astra1.initDepthStream();
    astra1.setDepthClipping(300, 5000);
    astra1.enableDepthImage(false);
    
    astra2.setup("device/sensor1");
    astra2.enableRegistration(bUseRegistration);
    astra2.initDepthStream();
    astra2.setDepthClipping(300, 5000);
    astra2.enableDepthImage(false);

    astra3.setup("device/sensor2");
    astra3.enableRegistration(bUseRegistration);
    astra3.initDepthStream();
    astra3.setDepthClipping(300, 5000);
    astra3.enableDepthImage(false);
    
    cam1FrameNum = 0;
    cam2FrameNum = 0;
    cam3FrameNum = 0;
    
}

void ofApp::update(){
    
    cout << "----- [ofApp::update()] Current Frame: " << ofGetFrameNum() << " -----" << endl;
    
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

    astra1.update();
    astra2.update();
    astra3.update();
    
    
    if(astra1.isFrameNew()){
        cout << "[ofApp::update()] Sensor0 isFrameNew() = true - Frame Num: " << cam1FrameNum << endl;
        cam1FrameNum++;
    }
    if(astra2.isFrameNew()){
        cout << "[ofApp::update()] Sensor1 isFrameNew() = true - Frame Num: " << cam2FrameNum << endl;
        cam2FrameNum++;
    }
    if(astra3.isFrameNew()){
        cout << "[ofApp::update()] Sensor2 isFrameNew() = true - Frame Num: " << cam3FrameNum << endl;
        cam3FrameNum++;
    }
    cout << "\n" << endl;
    
    img1.setFromPixels(astra1.getRawDepth());
    img2.setFromPixels(astra2.getRawDepth());
    img3.setFromPixels(astra3.getRawDepth());
    
}

void ofApp::draw(){


    ofSetColor(ofColor::white);
//    astra1.drawDepth(0, 0);
//    astra2.drawDepth(640, 0);
//    astra3.drawDepth(0, 480);
    
    img1.draw(0, 0);
    img2.draw(640, 0);
    img3.draw(0, 480);

	stringstream ss;
	ss << "r: toggle registration between color & depth images (";
	ss << (bUseRegistration ? "on)" : "off)") << endl;


	ofSetColor(ofColor::red);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 30);
    
    
    if(ofGetMouseX() > 0 && ofGetMouseX() < 640 && ofGetMouseY() > 0 && ofGetMouseY() < 480){
        
        ofSetColor(255);
        string s = ofToString(img1.getColor(ofGetMouseX(), ofGetMouseY()));
        ofDrawBitmapStringHighlight(s, ofGetMouseX(), ofGetMouseY());
        
//        cout << img1.getColor(ofGetMouseX(), ofGetMouseY()) << endl;
        
    }

}

void ofApp::keyPressed(int key){

	if (key == 'r') {
		bUseRegistration ^= 1;
		astra1.enableRegistration(bUseRegistration);
		astra2.enableRegistration(bUseRegistration);
//        astra3.enableRegistration(bUseRegistration);
    }
}
