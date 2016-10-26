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

class client
{
public:
    client(int ind,string i,int p,string n,bool r,bool m,bool s, bool live, bool hier);
    ~client();
    
    void setupSender();
    void sendData(ofxOscMessage &m);
    
    void setRigid(bool value);
    void setMarker(bool value);
    void setSkeleton(bool value);
    void draw();
    void drawGUI();
    ofRectangle &getArea();
    void isInside(int & x, int & y);
    void moveArea(int & x, int & y);
    void rearangePosition(int ind);

    
    int &getID();
    string &getIP();
    int &getPort();
    string &getName();
    bool &getRigid();
    bool &getMarker();
    bool &getSkeleton();
    bool &getLive();
    bool &getHierarchy();
    
    ofEvent<int> deleteClient;
    
private:
    ofVec2f         position;
    int             index;
    string          ip;
    int             port;
    string          name;
    bool            isRigid;
    bool            isMarker;
    bool            isSkeleton;
    bool            isLive;
    bool            deepHierarchy;
    
    
    ofRectangle     area;
    ofRectangle     rigButton;
    ofRectangle     markButton;
    ofRectangle     skelButton;
    ofRectangle     liveButton;
    ofRectangle     hierarchyButton;
    ofRectangle     delButton;
    
    ofTrueTypeFont	verdana14;
    
    ofxOscSender    sender;
    
};

#endif /* defined(__NatNet2OSCbridge__client__) */
