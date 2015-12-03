//
//  client.cpp
//  NatNet2OSCbridge
//
//  Created by Enrico Becker on 12.10.15.
//
//

#include "client.h"

client::client(int ind,string i,int p,string n,bool r,bool m,bool s)
{
    //arange them gridwise
    index = ind;
    ip = i;
    port = p;
    name = n;
    isRigid = r;
    isMarker = m;
    isSkeleton = s;
    int width = 30;
    int x = 340 * (index%2);
    int row = (index / 2);
    area = ofRectangle(x,row * (width * 2) + (row * 10), 330, width * 2);
    rigButton = ofRectangle(0, width, width, width);
    markButton = ofRectangle(100, width, width, width);
    skelButton = ofRectangle(200, width, width, width);
    delButton = ofRectangle(area.width - (width / 2), 0, width / 2, width / 2);
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    verdana14.loadFont("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    setupSender();
}

client::~client(){}

void client::rearangePosition(int ind)
{
    index = ind;
    int width = 30;
    int x = 340 * (index%2);
    int row = (index / 2);
    area = ofRectangle(x,row * (width * 2) + (row * 10), 330, width * 2);
    rigButton = ofRectangle(0, width, width, width);
    markButton = ofRectangle(100, width, width, width);
    skelButton = ofRectangle(200, width, width, width);
    delButton = ofRectangle(area.width - (width / 2), 0, width / 2, width / 2);
}


void client::setupSender()
{
    sender.setup(ip, port);
}

void client::sendData(ofxOscMessage &m)
{
    sender.sendMessage(m);
}


void client::draw()
{
    ofPushMatrix();
    ofTranslate(area.getX(),area.getY());
    drawGUI();
    string msg;
    msg += name + " ip " + ofToString(ip);
    msg += " : " + ofToString(port);

    ofSetColor(255,255,255);
    verdana14.drawString(msg, 20, 20);
    verdana14.drawString("Rigid", 40, 50);
    verdana14.drawString("Markers", 140, 50);
    verdana14.drawString("Skeleton", 240, 50);

    
    ofPopMatrix();
}

void client::drawGUI()
{
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofRect(0,0,area.getWidth(),area.getHeight());
    ofFill();
    if (!isRigid) ofSetColor(255, 0, 0);
    else ofSetColor(0,255,0);
    ofRect(rigButton);
    
    if (!isMarker) ofSetColor(255, 0, 0);
    else ofSetColor(0,255,0);
    ofRect(markButton);

    if (!isSkeleton) ofSetColor(255, 0, 0);
    else ofSetColor(0,255,0);
    ofRect(skelButton);
    
    ofSetColor(255, 255, 255);
    ofRect(delButton);
    ofSetColor(0, 0, 0);
    ofLine(delButton.x, delButton.y, delButton.x + delButton.width, delButton.y + delButton.height);
    ofLine(delButton.x + delButton.width, delButton.y, delButton.x, delButton.y + delButton.height);
}

void client::isInside(int & xp, int & yp)
{
    int x = xp - area.getX();
    int y = yp - area.getY();
    
    bool rig = rigButton.inside(x, y);
    bool mark = markButton.inside(x, y);
    bool skel = skelButton.inside(x, y);
    bool del = delButton.inside(x, y);

    if (rig) isRigid = !isRigid;
    
    else if (mark) isMarker = !isMarker;
    
    else if (skel) isSkeleton = !isSkeleton;
    
    else if (del) ofNotifyEvent(deleteClient,index);
}

string &client::getName()
{
    return name;
}


ofRectangle &client::getArea()
{
    return area;
}

int &client::getID()
{
    return index;
}


string &client::getIP()
{
    return ip;
}

int &client::getPort()
{
    return port;
}

void client::setRigid(bool value)
{
    isRigid = value;
}

void client::setMarker(bool value)
{
    isMarker = value;
}

void client::setSkeleton(bool value)
{
    isSkeleton = value;
}

bool &client::getRigid()
{
    return isRigid;
}

bool &client::getMarker()
{
    return isMarker;
}

bool &client::getSkeleton()
{
    return isSkeleton;
}
