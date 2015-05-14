//THIS CODE WAS DEVELOPED BY ANDREAS MULLER


#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void threshold( bool _upload );
    void draw();
    void resolutionChanged( int& _res );
    void keyPressed( int _key );
    
    ofParameter<int> resolution;
    ofParameter<float> noiseFrequency;
    ofParameter<bool> animate;
    
    ofParameter<bool> doThreshold;
    ofParameter<int> thresholdLow;
    ofParameter<int> thresholdHigh;
    ofParameter<bool> invert;
    
    int noiseStartX;
    int noiseStartY;
    
    ofImage noiseImage;
    
    ofxPanel gui;
    bool drawGui;
};
