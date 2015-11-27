#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(67,67,67);
    setupNatNet();
    setupClients();
    visible = true;
}

//--------------------------------------------------------------
void ofApp::update()
{
    natnet.update();
    sendOSC();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    string msg;
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i].draw();
    }
    
    if (visible)
    {
        string info;
        info += "natnet tracking informations: \n";
        info += "frames: " + ofToString(natnet.getFrameNumber()) + "\n";
        info += "data rate: " + ofToString(natnet.getDataRate()) + "\n";
        info += string("connected: ") + (natnet.isConnected() ? "YES" : "NO") + "\n";
        info += "num markers set: " + ofToString(natnet.getNumMarkersSet()) + "\n";
        info += "num marker: " + ofToString(natnet.getNumMarker()) + "\n";
        info += "num filterd (non regidbodies) marker: " +
        ofToString(natnet.getNumFilterdMarker()) + "\n";
        info += "num rigidbody: " + ofToString(natnet.getNumRigidBody()) + "\n";
        info += "num skeleton: " + ofToString(natnet.getNumSkeleton()) + "\n";
        info += "press s to save clients \n";
        info += "press h to hide the informations \n";
        
        ofSetColor(255);
        ofDrawBitmapString(info, 700, 20);
    }
}

void ofApp::setupNatNet()
{
    
    ofxXmlSettings natnetsettings("NatNetSetup.xml");
    int fps = natnetsettings.getValue("fps", 30);
    string interface = natnetsettings.getValue("interface", "en0");
    string natnetip = natnetsettings.getValue("ip", "10.200.200.13");
    natnet.setup(interface, natnetip);  // interface name, server ip
    natnet.setScale(100);
    natnet.setDuplicatedPointRemovalDistance(20);
    natnet.sendRequestDescription();
    ofSetFrameRate(fps);
}

void ofApp::setupClients()
{
    ofxXmlSettings settings;
    settings.load("clients.xml");
    int numClients = settings.getNumTags("client");
    for (int i = 0; i < numClients; i++)
    {
        settings.pushTag("client",i);
        string ip = settings.getValue("ip", "127.0.0.1");
        int port = settings.getValue("port", 1234);
        string name = settings.getValue("name", "unknown");
        bool r = settings.getValue("rigid", 0);
        bool m = settings.getValue("marker", 0);
        bool s = settings.getValue("skeleton", 0);
        clients.push_back(client(i,ip,port,name,r,m,s));
        settings.popTag();
    }
    for (int i = 0; i < numClients; i++)
    {
        clients[i].setupSender();
    }
}


void ofApp::sendOSC()
{
    sendAllMarkers();
    sendAllRigidBodys();
    sendAllSkeletons();
}

void ofApp::sendAllMarkers()
{
    bool isUsed = false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getMarker())
        {
            isUsed = true;
            break;
        }
    }
    if (isUsed)
    {
        for (int i = 0; i < natnet.getNumFilterdMarker(); i++)
        {
            ofxOscMessage m;
            m.setAddress("/marker");
            m.addIntArg(i);
            m.addFloatArg(natnet.getFilterdMarker(i).x);
            m.addFloatArg(natnet.getFilterdMarker(i).y);
            m.addFloatArg(natnet.getFilterdMarker(i).z);
            
            for (int j = 0; j < clients.size(); j++)
            {
                if(clients[j].getMarker()) clients[j].sendData(m);
            }
        }
    }
}

void ofApp::sendAllRigidBodys()
{
    bool isUsed = false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getRigid())
        {
            isUsed = true;
            break;
        }
    }

    if (isUsed)
    {
        vector<ofxNatNet::RigidBodyDescription> rbd = natnet.getRigidBodyDescriptions();
        for (int i = 0; i < natnet.getNumRigidBody(); i++)
        {
            const ofxNatNet::RigidBody &RB = natnet.getRigidBodyAt(i);
            // Get the matirx
            ofMatrix4x4 matrix = RB.matrix;
            
            // Decompose to get the different elements
            ofVec3f position;
            ofQuaternion rotation;
            ofVec3f scale;
            ofQuaternion so;
            matrix.decompose(position, rotation, scale, so);
            
            
            
            ofxOscMessage m;
            m.setAddress("/rigidBody");
            m.addIntArg(RB.id);
            m.addStringArg(ofToString(rbd[i].name));
            m.addFloatArg(position.x);
            m.addFloatArg(position.y);;
            m.addFloatArg(position.z);
            m.addFloatArg(rotation.x());
            m.addFloatArg(rotation.y());
            m.addFloatArg(rotation.z());
            m.addFloatArg(rotation.w());
            
            for (int j = 0; j < clients.size(); j++)
            {
                if(clients[j].getRigid()) clients[j].sendData(m);
            }
        }
    }
}

void ofApp::sendAllSkeletons()
{
    bool isUsed = false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getSkeleton())
        {
            isUsed = true;
            break;
        }
    }

    if (isUsed)
    {
        vector<ofxNatNet::SkeletonDescription> sd = natnet.getSkeletonDescriptions();
        for (int j = 0;  j < natnet.getNumSkeleton(); j++) {
            const ofxNatNet::Skeleton &S = natnet.getSkeletonAt(j);
            vector<ofxNatNet::RigidBodyDescription> rbd = sd[j].joints;

            ofxOscMessage m;
            m.setAddress("/skeleton");
            m.addStringArg(ofToString(sd[j].name));

            vector<ofVec3f> positions;
            for (int i = 0; i < S.joints.size(); i++)
            {
                const ofxNatNet::RigidBody &RB = S.joints[i];
                
                
                // Get the matirx
                ofMatrix4x4 matrix = RB.matrix;
                
                // Decompose to get the different elements
                ofVec3f position;
                ofQuaternion rotation;
                ofVec3f scale;
                ofQuaternion so;
                matrix.decompose(position, rotation, scale, so);
                m.addStringArg(ofToString(rbd[i].name));
                m.addFloatArg(position.x);
                m.addFloatArg(position.y);
                m.addFloatArg(position.z);
                m.addFloatArg(rotation.x());
                m.addFloatArg(rotation.y());
                m.addFloatArg(rotation.z());
                m.addFloatArg(rotation.w());
                
                
                positions.push_back(position);
            }
            
            for (int j = 0; j < clients.size(); j++)
            {
                if(clients[j].getSkeleton()) clients[j].sendData(m);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'h') visible = !visible;
    if (key == 's') saveClientsState();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    for (int i = 0; i < clients.size(); i++)
    {
        bool isInside = clients[i].getArea().inside(x, y);
        if (isInside)
        {
            clients[i].isInside(x, y);
            break;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::saveClientsState()
{
    ofxXmlSettings save;
    for (int i = 0; i < clients.size(); i++)
    {
         save.addTag("client");
         save.pushTag("client",i);
         save.addValue("ip", clients[i].getIP());
         save.addValue("port", clients[i].getPort());
         save.addValue("name", clients[i].getName());
         save.addValue("rigid", clients[i].getRigid());
         save.addValue("marker", clients[i].getMarker());
         save.addValue("skeleton", clients[i].getSkeleton());
         save.popTag();
    }
    save.save("clients.xml");
}


void ofApp::exit()
{
}

