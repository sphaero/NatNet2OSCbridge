#pragma once

#include "ofMain.h"

#include "ofxNatNet.h"
#include "ofxXmlSettings.h"
#include "client.h"
#include "ofxImGui.h"
#include "uiWidgets.h"
#include "ofpy.h"
#include "ImNodes.h"

//for velocity, defines how many layers to apply (2 * layers + 1 frames)
#define SMOOTHING 0

class RigidBodyHistory {
public:
    int                 rigidBodyId;
    ofVec3f             velocities[2 * SMOOTHING + 1];
    ofVec3f             angularVelocities[2 * SMOOTHING + 1];
    int                 currentDataPoint;
    ofVec3f             previousPosition;
    ofQuaternion        previousOrientation;
    bool                firstRun;
    int                 framesInactive;
    
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
    
    void setupConnectionInterface();
    void setupData(string filename);
    void addClient(int i,string ip,int p,string n,bool r,bool m,bool s,bool live, bool hierarchy, int modeFlags, float posX, float posY);
    void sendOSC();
    
    bool connectNatnet(string interfaceName, string interfaceIP);
    
    void saveData(string filepath);
    void deleteClient(int &index);
    
    void setFeedback(string feedbackText);
    
    //GUI
    ofxImGui::Gui gui;
    bool guiVisible;
    bool mouseOverGui;
    void doGui();
    ImFont* fontDefault;
    ImFont* fontSubTitle;
    ImFont* fontTitle;
    uiLogger uiLogWidget;

    ImNodes::CanvasState* gCanvas = nullptr;
    
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
    
    string userDataDir;
    string UserFeedback;
    
    bool                visible;
    bool                connected;
    bool                triedToConnect;
    bool                openModal;
    int                 numRigidBody;
    int                 numSkeleton;
    bool                running;
    int                 rigidBodySize;
    int                 skeletonSize;
    int                 InterfaceX;
    int                 InterfaceY;
    
   
    //gui stuff
    float               invFPS;
    int                 FPS;
    char                natnetip_char[16];
    char*                save_fileName;
    int                 current_iface_idx;
    vector<string>      iface_list;
    ImVec2              mocap_node_pos = {20,20};
    bool                mocap_node_selected = false;
    ImNodes::Ez::SlotInfo mocap_node_outputs[3] = {
        { "RigidBodies", 1 },
        { "Markers", 1 },
        { "Skeletons", 1 }
    };

};
