//
//  client.h
//  NatNet2OSCbridge
//
//  Created by Enrico Becker on 12.10.15.
//
//

#ifndef __NatNet2OSCbridge__client__
#define __NatNet2OSCbridge__client__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxImGui.h"

//TODO: replace with filters!
enum ClientMode
{
    ClientMode_Default      = 0,
    ClientMode_GearVR       = 1,
    ClientMode_FullSkeleton = 2,
    ClientMode_END          = 3
};

static const char* ClientModeNames[] =
{
    "Default",
    "Gear VR",
    "Full Skeleton",
    "INVALID"
};

class client
{
public:
    client(int ind,string i,int p,string n,bool r,bool m,bool s, bool live, bool hier, ClientMode mode);
    ~client();
    
    void setupSender();
    void sendData(ofxOscMessage &m);
    void sendBundle(ofxOscBundle &b);
    
    void setRigid(bool value);
    void setMarker(bool value);
    void setSkeleton(bool value);
    void doGui();
    
    int &getID();
    string &getIP();
    int &getPort();
    string &getName();
    bool &getRigid();
    bool &getMarker();
    bool &getSkeleton();
    bool &getLive();
    bool &getHierarchy();
    ClientMode &getMode();

    ofEvent<int> deleteClient;
    
private:
    int             index;
    string          ip;
    int             port;
    string          name;
    bool            isRigid;
    bool            isMarker;
    bool            isSkeleton;
    bool            isLive;
    bool            deepHierarchy;
    ClientMode      mode;
    ofxOscSender    sender;

    char*            rigidstr;
    char*            markstr;
    char*            skelstr;
    char*            hierstr;
};

#endif /* defined(__NatNet2OSCbridge__client__) */
