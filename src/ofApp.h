#pragma once

#include "ofMain.h"

#include "ofxNatNet.h"
#include "ofxXmlSettings.h"
#include "client.h"
#include "ofxTextInputField.h"
#include "ofxTextButton.h"


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
    void addClient(int i,string ip,int p,string n,bool r,bool m,bool s);
    void sendOSC();
    
    bool connectNatnet();
    
    void deactivateInputs();
    void saveData();
    void deleteClient(int &index);
    
private:
    void                    sendAllMarkers();
    void                    sendAllRigidBodys();
    void                    sendAllSkeletons();

    ofxNatNet               natnet;
    
    vector<client*>         clients;
    
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
};
