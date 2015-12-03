#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(67,67,67);
    setupInputfields();
    setupData();
    visible = true;
    numRigidBody = 0;
    numSkeleton = 0;
    running = true;
    font.loadFont("verdana.ttf", 12);
    addButton.setup(ofRectangle(960, 260, 80, 20), "Add User", 12, ofColor(0,0,0), ofColor(255,255,255));
    connect.setup(ofRectangle(960, 110, 80, 20), "Connect", 12, ofColor(0,0,0), ofColor(255,255,255));
}

void ofApp::setupData()
{
    ofxXmlSettings data("setup.xml");
    data.pushTag("setup",0);
    int fRate = data.getValue("fps", 30);
    string interface = data.getValue("interface", "en0");
    string natnetip = data.getValue("ip", "10.200.200.13");
    interfaceName.setText(interface);
    interfaceIP.setText(natnetip);
    fps.setText(ofToString(fRate));
    
/*    natnet.setup(interface, natnetip);  // interface name, server ip
    if(natnet.isConnected())
    {
        natnet.setScale(100);
        natnet.setDuplicatedPointRemovalDistance(20);
        natnet.sendRequestDescription();
    }*/
    ofSetFrameRate(fRate);
    data.popTag();

    int numClients = data.getNumTags("client");
    for (int i = 0; i < numClients; i++)
    {
        data.pushTag("client",i);
        string ip = data.getValue("ip", "127.0.0.1");
        int port = data.getValue("port", 1234);
        string name = data.getValue("name", "unknown");
        bool r = data.getValue("rigid", 0);
        bool m = data.getValue("marker", 0);
        bool s = data.getValue("skeleton", 0);
        addClient(i,ip,port,name,r,m,s);
        data.popTag();
    }
}


void ofApp::setupInputfields()
{
    interfaceName.setup(ofRectangle(700, 50, 140, 20), 10, "en0","Interface");
    interfaceIP.setup(ofRectangle(700, 80, 140, 20), 10, "127.0.0.1","Natnet IP");
    fps.setup(ofRectangle(700, 110, 140, 20), 10, "30","FPS");

    newName.setup(ofRectangle(700, 200, 140, 20), 10, "New Client","Client Name");
    newIP.setup(ofRectangle(700, 230, 140, 20), 10, "127.0.0.1","Client IP");
    newPort.setup(ofRectangle(700, 260, 140, 20), 10, "6200","Client Port");
}

bool ofApp::connectNatnet()
{
    cout << "connect to natnet" << endl;
    natnet.setup(interfaceName.getText(), interfaceIP.getText());  // interface name, server ip
    if(natnet.isConnected())
    {
        natnet.setScale(100);
        natnet.setDuplicatedPointRemovalDistance(20);
        natnet.sendRequestDescription();
        return true;
    }
    return false;
}


//--------------------------------------------------------------
void ofApp::update()
{
    if(running)
    {
        natnet.update();
        sendOSC();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    string msg;
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->draw();
    }
    
    if (visible)
    {
        font.drawString("Global Settings", 700, 30);
        interfaceName.draw();
        interfaceIP.draw();
        fps.draw();
        connect.draw();

        font.drawString("New User", 700, 180);
        
        newName.draw();
        newIP.draw();
        newPort.draw();
        
        addButton.draw();
        
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
        info += string("press p to pause clients, is paused: ") + (running ? "NO" : "YES") + "\n";
        info += "press s to save clients \n";
        info += "press h to hide the informations \n";
        
        ofSetColor(255);
        ofDrawBitmapString(info, 700, 350);
    }
}

void ofApp::addClient(int i,string ip,int p,string n,bool r,bool m,bool s)
{
    client *c = new client(i,ip,p,n,r,m,s);
    ofAddListener(c->deleteClient, this, &ofApp::deleteClient);
    clients.push_back(c);
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
        if (clients[i]->getMarker())
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
                if(clients[j]->getMarker()) clients[j]->sendData(m);
            }
        }
    }
}

void ofApp::sendAllRigidBodys()
{
    bool isUsed = false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getRigid())
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
                if(clients[j]->getRigid()) clients[j]->sendData(m);
            }
        }
    }
}

void ofApp::sendAllSkeletons()
{
    bool isUsed = false;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getSkeleton())
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
            m.addIntArg(S.id);
            m.addStringArg(ofToString(sd[j].name));

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
            }
            
            for (int j = 0; j < clients.size(); j++)
            {
                if(clients[j]->getSkeleton()) clients[j]->sendData(m);
            }
        }
    }
}

void ofApp::deactivateInputs()
{
    //deactivate all inputfields
    interfaceName.deactivate();
    interfaceIP.deactivate();
    fps.deactivate();
    newName.deactivate();
    newIP.deactivate();
    newPort.deactivate();
}

void ofApp::deleteClient(int &index)
{
    cout << "delete " << index << endl;
    ofRemoveListener(clients[index]->deleteClient, this, &ofApp::deleteClient);
    delete clients[index];
    clients.erase(clients.begin() + index);
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->rearangePosition(i);
    }    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //first check the input fields
    if (interfaceName.getState())
    {
        interfaceName.addKey(key);
        return;
    }
    if (interfaceIP.getState())
    {
        interfaceIP.addKey(key);
        return;
    }
    if (fps.getState())
    {
        fps.addKey(key);
        return;
    }
    if (newName.getState())
    {
        newName.addKey(key);
        return;
    }
    if (newIP.getState())
    {
        newIP.addKey(key);
        return;
    }
    if (newPort.getState())
    {
        newPort.addKey(key);
        return;
    }
    
    if (key == 'h') visible = !visible;
    if (key == 's') saveData();
    if (key == 'p')
    {
        running = !running;
        if (running) natnet.sendRequestDescription();
    }
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
        bool isInside = clients[i]->getArea().inside(x, y);
        if (isInside)
        {
            clients[i]->isInside(x, y);
            return;
        }
    }
    if(interfaceName.isInside(x, y)) return;
    if(interfaceIP.isInside(x, y)) return;
    if(fps.isInside(x, y)) return;
    if(newName.isInside(x, y)) return;
    if(newIP.isInside(x, y)) return;
    if(newPort.isInside(x, y)) return;
    if(addButton.isInside(x, y))
    {
        deactivateInputs();
        addClient(clients.size(), newIP.getText(), ofToInt(newPort.getText()), newName.getText(), false, false, false);
        return;
    }
    if (connect.isInside(x, y)) connectNatnet();
    deactivateInputs();
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

void ofApp::saveData()
{
    ofxXmlSettings save;
    save.addTag("setup");
    save.pushTag("setup",0);
    save.addValue("fps", ofToInt(fps.getText()));
    save.addValue("interface", interfaceName.getText());
    save.addValue("ip", interfaceIP.getText());
    save.popTag();
    for (int i = 0; i < clients.size(); i++)
    {
        save.addTag("client");
        save.pushTag("client",i);
        save.addValue("ip", clients[i]->getIP());
        save.addValue("port", clients[i]->getPort());
        save.addValue("name", clients[i]->getName());
        save.addValue("rigid", clients[i]->getRigid());
        save.addValue("marker", clients[i]->getMarker());
        save.addValue("skeleton", clients[i]->getSkeleton());
        save.popTag();
    }
    save.save("setup.xml");
}


void ofApp::exit()
{
    for (int i = 0; i < clients.size(); i++)
    {
        delete clients[i];
    }
}

