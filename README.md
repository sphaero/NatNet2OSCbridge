# NatNet2OSCbridge

MOCAP data to OSC

## Feature overview

The NatNet2OSCbridge decodes a NatNet stream from Motive into OSC, which it can then send to clients.

Clients are simply added by an ipaddress/hostname and port number combination.

### Client Settings

<b>Rigidbodies</b><br>
If checked client will receive the rigidbodies found in the NatNet stream

<b>Markers</b><br>
If checked client will receive the markers found in the NatNet stream

<b>Skeletons</b><br>
If checked client will receive the skeletons found in the NatNet stream

<b>Hierarchy</b><br>
If checked client will receive skeletons as a bundle of messages (e.g. "/skeleton/name/bone/") instead of receiving an entire skeleton in a single message ("/skeleton")

<b>Velocity</b><br>
If checked client will receive the the velocity data of rigidbodies. This implies a single frame delay.

<b>Full</b><br>
If checked client will receive the skeletons with bone parenting structure (specifically for use with our UnityOSCToolkit)

### Save/Load Setup

Setups of clients and global settings can be loaded and saved by using the "Save Setup" and "Load Setup" button. Files are plain text XML files, a default file "setup.xml" is loaded at startup if it exists.

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

