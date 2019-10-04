#ifndef MIDINODE_H
#define MIDINODE_H
#include "ofMain.h"
#include "ofxMidi.h"

class midiNode : public ofxMidiListener
{
public:
    midiNode()
    {
        midiIn.listInPorts();
        midiIn.ignoreTypes(false, false, false);
        midiIn.addListener(this);
        refreshDevices();
    }

    virtual ~midiNode()
    {
        midiIn.closePort();
        midiIn.removeListener(this);
    }

    void newMidiMessage(ofxMidiMessage& msg)
    {
        lock.lock(); //  see https://github.com/danomatika/ofxMidi/issues/76
        midiMessages.push_back(msg);
        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
            midiMessages.erase(midiMessages.begin());
        }
        lock.unlock();
    }

    void refreshDevices() {
        ofLogNotice("ofxMidiIn") << midiIn.getNumInPorts() << " ports available";
        midiDevices.clear();
        midiDevices = midiIn.getInPortList();
        midiDevices.insert(midiDevices.begin(), "none");
    }

    void doGui()
    {

    }

    ofxMidiIn midiIn;
    std::vector<ofxMidiMessage> midiMessages;
    std::vector<string> midiDevices;
    int currentDevice = 0;
    string currentDeviceName= "";
    std::size_t maxMessages = 100; //< max number of messages to keep track of
    ofMutex lock;
    bool sendRaw = false;
    bool verbose = false;
    bool ignoreSysex= false;
    bool ignoreTiming = false;
    bool ignoreSense = false;
};

#endif // MIDINODE_H
