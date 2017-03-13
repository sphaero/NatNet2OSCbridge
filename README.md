# NatNet2OSCbridge

## Feature overview
The bridge uses ofxNatNet to decode a natnet stream from Motive into OSC, which it can then broadcast to clients.

Clients are added manually, and contain the following settings:
- Name
- IP Address
- Port

### Settings
<b>Data</b><br>
Once added, they can receive Rigidbodies, Skeletons and Markers through the three green/red switches at the top of their client-box.

<b>Hierarchy</b><br>
On the right you can select if this client wants to receive <b>Hierarchical</b> OSC data, meaning for example that instead of receiving an entire skeleton in a single message "/skeleton", you will receive it as a bundle of messages with different addresses (e.g. "/skeleton/name/bone/")

<b>Live</b><br>
This is a WIP option that will be used in future to select pre-recorded, stored motion capture data. This will allow clients to receive different pre-recorded motion capture data, instead of having to send either live/recorded data to everybody from Motive.

<b>Client Modes</b><br>
Currently there are 3 client modes:
- Default: sends messages normally.
- GearVR: WIP, sends smaller amount of data to reduce latency.
- Full-Skeleton: Includes bone parenting structure for skeletons, specifically for use with our UnityOSCToolkit.

### Save/Load
Setups can be saved by hitting the "Save" button. This writes an XML file that is automatically loaded when reopening.

### More MOCAP information and Manual

https://drive.google.com/drive/u/0/folders/0BzwxZounZTt9bjYxWmlnRGZYRE0
