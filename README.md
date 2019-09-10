# NatNet2OSCbridge

<img align="right" width="450" src="https://i.imgur.com/zGxigBk.png">

MOCAP data to OSC.

Download the latests version for your platform at the [releases tab](https://github.com/hku-ect/NatNet2OSCbridge/releases)

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

* Mode ONE with Hierarchy **unchecked**
* Mode TWO with Hierarchy **checked**

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

The units are floats and can either be in meters or centimeters depending on the recording.

#### Skeleton message: `/skeleton/<NameOfSkeleton>/<NameOfJoint>`

The OSC message consist of a message with the label `/skeleton/<NameOfSkeleton>/<NameOfJoint>` and contains 14 values:

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

The units are floats and can either be in meters or centimeters depending on the recording.

## Mode TWO with Hierarchy switched <b>ON</b>

#### Rigidbody message: `/rigidbody/<NameRigidBody>`

The OSC message consist of a message with the label `/rigidbody/<NameRigidBody>` and contains 15 values:

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

The units are floats and can either be in meters or centimeters depending on the recording.

#### Skeleton message: `/skeleton/<NameOfSkeleton>/<NameOfJoint>`

The OSC message consist of a message with the label `/skeleton/<NameOfSkeleton>/<NameOfJoint>` and contains 14 values:

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

The units are floats and can either be in meters or centimeters depending on the recording.

# Build instructions

This application is build upon [OpenFrameworks](https://github.com/openframeworks/openframeworks). In order to build this application you will need openframeworks installed.

The following steps need to be taken to build the application from git repositories. Please note that all these steps require the GNU build tools (make). Instructions do not cover Xcode or VisualStudio!

* 1: clone openframeworks: git clone https://github.com/openframeworks/openframeworks.<br>Follow the [instructions for your platform](https://github.com/openframeworks/openFrameworks/blob/master/INSTALL_FROM_GITHUB.md)
* 2: clone our ofxNatNet fork to the addons dir: `git clone https://github.com/hku-ect/ofxNatNet.git`
* 3: clone the ofxImGui addon: `git clone https://github.com/jvcleave/ofxImGui.git`
* 4: recurse clone the NatNet2OSCbridge repository to the apps devApps dir: `git clone --recurse-submodules https://github.com/hku-ect/NatNet2OSCbridge.git`
* 5.1: On OSX configure and build the python library:<br/> `brew install openssl xz; cd ext/cpython; ./configure --prefix $(pwd /../../bin/python) --disable-shared --with-openssl=$(brew --prefix openssl); make; make install; cd -`
* 5.2: On Linux configure and build the python library: <br/>`cd ext/cpython; ./configure --prefix $HOME/openFrameworks/apps/devApps/$APPNAME/bin/python --
disable-shared && make -s && make install; cd -`
* 5.3: On Windows run: `make python_win`
* 6: Build the application: `make Debug` or `make Release`
* 7: You'll find the application in the `bin` directory.
