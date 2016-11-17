#pragma once

#include "ofMain.h"

#include "ofxNatNet.h"
#include "ofxXmlSettings.h"
#include "client.h"
#include "ofxTextInputField.h"
#include "ofxTextButton.h"

//for velocity, defines how many layers to apply (2 * layers + 1 frames)
#define SMOOTHING 3

class RigidBodyHistory {
public:
    int                 rigidBodyId;
    ofVec3f             velocities[2 * SMOOTHING + 1];
    ofVec3f             angularVelocities[2 * SMOOTHING + 1];
    int                 currentDataPoint;
    ofVec3f             previousPosition;
    ofQuaternion        previousOrientation;
    bool                firstRun;
    
    RigidBodyHistory( int rigidBodyId, ofVec3f position, ofQuaternion eulerOrientation );
};

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
    
    void setupInputfields();
    void setupData();
    void addClient(int i,string ip,int p,string n,bool r,bool m,bool s,bool live, bool hierarchy, ClientMode mode);
    void sendOSC();
    
    bool connectNatnet();
    
    void deactivateInputs();
    void saveData();
    void deleteClient(int &index);
    
private:
    void                    sendAllMarkers();
    void                    sendAllRigidBodys();
    void                    sendAllSkeletons();
    
    void                    getMarkers(         client *c, ofxOscBundle *bundle );
    void                    getRigidbodies(     client *c, ofxOscBundle *bundle,
                                                    vector<ofxNatNet::RigidBodyDescription> rbd );
    void                    getSkeletons(       client *c, ofxOscBundle *bundle,
                                                    vector<ofxNatNet::SkeletonDescription> sd );
    
    void                    fixRanges( ofVec3f *euler );
    ofVec3f                 shortestRotation( ofVec3f euler );

    ofxNatNet               natnet;
    
    vector<client*>             clients;
    vector<RigidBodyHistory>    rbHistory;
    
    string folder;
    
    bool                visible;
    bool                connected;
    int                 numRigidBody;
    int                 numSkeleton;
    bool                running;
    int                 rigidBodySize;
    int                 skeletonSize;
    
    ofTrueTypeFont      font;
    //gui stuff
    
    ofxTextInputField   interfaceName;
    ofxTextInputField   interfaceIP;
    ofxTextInputField   fps;
    
    ofxTextInputField   newName;
    ofxTextInputField   newIP;
    ofxTextInputField   newPort;
    
    ofxTextButton       addButton;
    ofxTextButton       saveButton;
    ofxTextButton       connect;
    
    float               invFPS;
};
