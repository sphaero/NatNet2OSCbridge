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

## OSC Data Structure

In the NatNet2OSCbridge there are two modes of sending the data over OSC. 
- Mode ONE with Hierarchy switched <b>OFF</b>
- Mode TWO with Hierarchy switched <b>ON</b>

## Mode ONE with Hierarchy switched <b>OFF</b>

#### Rigidbody message: `/rigidbody`

The OSC message consist of a message with with the label `/rigidbody` and contains 15 values:

- Value 00: ID (int) of rigidbody
- Value 01: Name (string) of rigidbody
- Value 02: X position of rigidbody
- Value 03: Y position of rigidbody
- Value 04: Z position of rigidbody
- Value 05: X rotation of rigidbody (Quarternion)
- Value 06: Y rotation of rigidbody (Quarternion)
- Value 07: Z rotation of rigidbody (Quarternion)
- Value 08: W rotation of rigidbody (Quarternion)
- Value 09: X position velocity of rigidbody
- Value 10: Y position velocity of rigidbody
- Value 11: Z position velocity of rigidbody
- Value 12: X rotation velocity of rigidbody (Euler)
- Value 13: Y rotation velocity of rigidbody (Euler)
- Value 14: Z rotation velocity of rigidbody (Euler)

#### Example:

`/rigidbody 0 Blokje2 0.995632 0.025337 0.034089 0.083149 0.995632 0.025337 0.034089`

The units are floats and can either be in meters of centimeters depending on the recording.

#### Skeleton message: `/skeleton/<NameOfSkeleton>/<NameOfJoint>`

The OSC message consist of a message with with the label `/skeleton/<NameOfSkeleton>/<NameOfJoint>` and contains 14 values:

- Value 00: Name (string) of the skeleton joint
- Value 01: X position of skeleton joint
- Value 02: Y position of skeleton joint
- Value 03: Z position of skeleton joint
- Value 04: X rotation of skeleton joint (Quarternion)
- Value 05: Y rotation of skeleton joint (Quarternion)
- Value 06: Z rotation of skeleton joint (Quarternion)
- Value 07: W rotation of skeleton joint (Quarternion)
- Value 08: X position velocity of skeleton joint
- Value 09: Y position velocity of skeleton joint
- Value 10: Z position velocity of skeleton joint
- Value 11: X rotation velocity of skeleton joint (Euler)
- Value 12: Y rotation velocity of skeleton joint (Euler)
- Value 13: Z rotation  velocityof skeleton joint (Euler)

#### Examples:

`/skeleton/Jan/Hip Hip -2.36176 0.856184 -0.603909 0.083149 0.995632 0.025337 0.034089`

`/skeleton/Jan/Ab Ab -2.34777 0.940245 -0.599119 0.071686 0.996859 0.00257 0.033565`

The units are floats and can either be in meters of centimeters depending on the recording.

## Mode TWO with Hierarchy switched <b>ON</b>

#### Rigidbody message: `/rigidbody/<NameRigidBody>`

The OSC message consist of a message with with the label `/rigidbody/<NameRigidBody>` and contains 15 values:

- Value 00: ID (int) of rigidbody
- Value 01: Name (string) of rigidbody
- Value 02: X position of rigidbody
- Value 03: Y position of rigidbody
- Value 04: Z position of rigidbody
- Value 05: X rotation of rigidbody (Quarternion)
- Value 06: Y rotation of rigidbody (Quarternion)
- Value 07: Z rotation of rigidbody (Quarternion)
- Value 08: W rotation of rigidbody (Quarternion)
- Value 09: X position velocity of rigidbody
- Value 10: Y position velocity of rigidbody
- Value 11: Z position velocity of rigidbody
- Value 12: X rotation velocity of rigidbody (Euler)
- Value 13: Y rotation velocity of rigidbody (Euler)
- Value 14: Z rotation velocity of rigidbody (Euler)

#### Example:

`/rigidbody 0 Blokje2 0.995632 0.025337 0.034089 0.083149 0.995632 0.025337 0.034089`

The units are floats and can either be in meters of centimeters depending on the recording.

#### Skeleton message: `/skeleton/<NameOfSkeleton>/<NameOfJoint>`

The OSC message consist of a message with with the label `/skeleton/<NameOfSkeleton>/<NameOfJoint>` and contains 14 values:

- Value 00: Name (string) of the skeleton joint
- Value 01: X position of skeleton joint
- Value 02: Y position of skeleton joint
- Value 03: Z position of skeleton joint
- Value 04: X rotation of skeleton joint (Quarternion)
- Value 05: Y rotation of skeleton joint (Quarternion)
- Value 06: Z rotation of skeleton joint (Quarternion)
- Value 07: W rotation of skeleton joint (Quarternion)
- Value 08: X position velocity of skeleton joint
- Value 09: Y position velocity of skeleton joint
- Value 10: Z position velocity of skeleton joint
- Value 11: X rotation velocity of skeleton joint (Euler)
- Value 12: Y rotation velocity of skeleton joint (Euler)
- Value 13: Z rotation  velocityof skeleton joint (Euler)

#### Examples:

`/skeleton/Jan/Hip Hip -2.36176 0.856184 -0.603909 0.083149 0.995632 0.025337 0.034089`

`/skeleton/Jan/Ab Ab -2.34777 0.940245 -0.599119 0.071686 0.996859 0.00257 0.033565`

The units are floats and can either be in meters of centimeters depending on the recording.

