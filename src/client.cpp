//
//  client.cpp
//  NatNet2OSCbridge
//
//  Created by Enrico Becker on 12.10.15.
//
//

#include "client.h"
#include "fontawesome5.h"
#include "ect_helpers.h"

client::client(int ind,string i,int p,string n,bool r,bool m,bool s, bool live, bool vrt, bool hier, int mFlags, bool midi, bool osc )
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
    recvVRTrackers = vrt;
    deepHierarchy = hier;
    modeFlags = mFlags;
    setupSender();

    rigidstr = "Rigid##" + ip + ofToString(port);
    markstr = "Mark##" + ip + ofToString(port);
    skelstr = "Skel##" + ip + ofToString(port);
    hierstr = "Hier##" + ip + ofToString(port);
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

void client::doGui()
{
    //Without PushID/PopID all the client combo's & flag checkboxes start to conflict...
    ImGui::PushID(index);

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
    
    ImGui::Checkbox(rigidstr.c_str(), &isRigid);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send rigidbodies");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();
    
    ImGui::Checkbox(markstr.c_str(), &isMarker);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send markers");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();
    
    ImGui::Checkbox(skelstr.c_str(), &isSkeleton);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send Skeletons");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();

    ImGui::Checkbox(hierstr.c_str(), &deepHierarchy);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send hierarchy of skeletons joints");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();

    //DISCUSS: We could turn this into a drop-down flag list as well, with checkboxes. Hierarchy could be moved to this as well.
    //We can use the BeginCombo/EndCombo example from ImGui to do this...
    for ( int i = 0; i < clientMode_list.size(); ++i ) {
        ImGui::SameLine();

        int mask = pow(2, i);
        bool b = (modeFlags & mask);

        if (ImGui::Checkbox(clientMode_list[i].first.c_str(), &b)) {
            if (b) {
                ofLogVerbose("Enabled " + clientMode_list[i].second);
                modeFlags |= mask;
            }
            else {
                ofLogVerbose("Disabled " + clientMode_list[i].second);
                modeFlags &= ~mask;
            }
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(clientMode_list[i].second.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
    ImGui::SameLine();
    ImGui::Checkbox("Midi", &recvMidi);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send midi data");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
    ImGui::SameLine();
    ImGui::Checkbox("OSC", &recvOSC);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send received OSC data");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }

    ImGui::Checkbox("VRTrackers", &recvVRTrackers);
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("Send VRTrackers data");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }

    ImGui::PopID();

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

int &client::getModeFlags()
{
    return modeFlags;
}
