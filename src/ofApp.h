#pragma once

#include "ofMain.h"

#include "ofxNatNet.h"
#include "ofxXmlSettings.h"
#include "client.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupNatNet();
    void setupClients();
    void sendOSC();
    
    void saveClientsState();
    void somethingChanged();
    
    
private:
    void                    sendAllMarkers();
    void                    sendAllRigidBodys();
    void                    sendAllSkeletons();

    ofxNatNet               natnet;
    
    vector<client>          clients;
    
    string folder;
    
    bool visible;
    int numRigidBody;
    int numSkeleton;
};
