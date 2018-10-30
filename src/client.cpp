//
//  client.cpp
//  NatNet2OSCbridge
//
//  Created by Enrico Becker on 12.10.15.
//
//

#include "client.h"
#include "fontawesome5.h"

client::client(int ind,string i,int p,string n,bool r,bool m,bool s, bool live, bool hier, ClientMode cMode )
{
    //arange them gridwise
    index = ind;
    ip = i;
    port = p;
    name = n;
    isRigid = r;
    isMarker = m;
    isSkeleton = s;
    isLive = live;
    deepHierarchy = hier;
    mode = cMode;
    setupSender();
}

client::~client(){}

void client::setupSender()
{
    sender.setup(ip, port);
}

void client::sendData(ofxOscMessage &m)
{
    sender.sendMessage(m);
}

void client::sendBundle(ofxOscBundle &b)
{
    sender.sendBundle(b);
}

void client::draw()
{   
    ImGui::Text(ICON_FA_BROADCAST_TOWER);
    ImGui::SameLine();
    //ImGui::Text(name.c_str());
    ImGui::Text("ip:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.7f,1.0f,1.0f,1.0f), ip.c_str());
    ImGui::SameLine();
    ImGui::Text("port:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.5f,0.3f,1.0f,1.0f), "%d", port);
    ImGui::Checkbox("Rigid", &isRigid);
    ImGui::SameLine();
    ImGui::Checkbox("Mark", &isMarker);
    ImGui::SameLine();
    ImGui::Checkbox("Skel", &isSkeleton);
    ImGui::SameLine();
    ImGui::Checkbox("Hierarchy", &deepHierarchy);
    
    //ImGui::Spacing();
    //ImGui::Separator();
    //ImGui::Spacing();
}

string &client::getName()
{
    return name;
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

bool &client::getLive()
{
    return isLive;
}

bool &client::getHierarchy()
{
    return deepHierarchy;
}

ClientMode &client::getMode()
{
    return mode;
}
