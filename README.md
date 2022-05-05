
### Development Tips
You'll need Unreal Engine 4.25 and Visual Studio 2019 to develop. Most work can be done in the Unreal Engine editor on the blueprints, but some things (especially the ROSIntegration stuff) need to be done in VS. If something seems overcomplicated or suboptimal, chances are I had to do it that way to get things working.

Ideally for things like takeoff and landing we would use ROS actions to robustly and flexibly handle things like takeoff. Unfortunately the ROSIntegration plugin for UE4 does not support actions.
Alternatively we could use services and have the drone respond whenever it is done with the task. Unfortunately the ROSIntegration plugin does not support services running for longer than five seconds.
What we have to do is run a service to let the drone know to take off, and the response is simply an ack. Then the drone will use a different service to let us know it finished.
I initially did this with messages but sometimes they get dropped and I didn't want to deal with the extra complexity of all the acks going back and forth.

I recommend playing in standalone, offline mode. Running in editor causes weird problems when connecting to ROS. Offline is required because the user decides if a game will be a server or the client, so UE4's native attempt to automatically start a server will interfere.

For my evaluation environment I run at least two game instances, as well as an Ubuntu virtual machine to handle the Gazebo simulation and ROS stuff.

The most important parameter to change is the ROS bridge IP, which is set in the Content/ROS/Blueprints/BP_ROS_GAME. If your game starts with a black screen and appears unresponsive, it is most likely
that it is blocking on attempting to connect to the server.


### Software Explanation

Most important stuff happens in the quadcopter blueprint

[This forum post](https://forums.unrealengine.com/t/game-state-game-instance-game-mode-which-one-to-use-for-what/399795/2) is very helpful for understanding how to use the various network-related components of an Unreal Engine game. The page also includes a link to the network compendium, which goes into even more detail.

To toggle minimap between follow player and fixed orientation, go to quadcopter blueprint and change the spring arm holding the overhead screen capture object. The property to change is "inherit yaw"

### Trouble building (missing symbols about topic / service conversion)?

1. Delete sln/intermediate/saved/binaries\
1. Use bat file to rebuild ROSIntegration plugin
1. generate visual studio files (to make new sln)
1. build again

### Licensed content required:
[Quadcopters](https://unrealengine.com/marketplace/en-US/product/quadcopters) package. When you add the files back in don't forget to remove the gitignores. Add the following file structure

Content/Quadcopters/ \
&emsp;    /Cue \
&emsp;&emsp;        /SC_QuadcoptersAudio.uasset \
&emsp;    /Materials \
&emsp;&emsp;        /Inner_Collision.uasset \
&emsp;&emsp;        /M_QuadcopterA_Master_01.uasset \
&emsp;&emsp;        /M_QuadcopterA_Master_02.uasset \
&emsp;&emsp;        /MI_QuadcopterA_01.uasset \
&emsp;&emsp;        /MI_QuadcopterA_02.uasset \
&emsp;&emsp;        /MI_QuadcopterA_03.uasset \
&emsp;&emsp;        /MI_QuadcopterA_04_BLUE.uasset \
&emsp;&emsp;        /Outer_Collision.uasset \
&emsp;    /Mesh \
&emsp;&emsp;        /SM_QuadcopterA_Cam.uasset \
&emsp;&emsp;        /SM_QuadcopterA_Main.uasset \
&emsp;&emsp;        /SM_QuadcopterA_Rotor.uasset \
&emsp;    /Textures \
&emsp;&emsp;        /T_QuadcopterA_BC_01.uasset \
&emsp;&emsp;        /T_QuadcopterA_BC_02.uasset \
&emsp;&emsp;        /T_QuadcopterA_M_01.uasset \
&emsp;&emsp;        /T_QuadcopterA_M_02.uasset \
&emsp;&emsp;        /T_QuadcopterA_M_03.uasset \
&emsp;&emsp;        /T_QuadcopterA_M_04.uasset \
&emsp;&emsp;        /T_QuadcopterA_N.uasset \
&emsp;    /Wav \
&emsp;&emsp;        /S_QuadcoptersAudio.uasset



The files in Content/Quidditch_Assets were taken from this [package of quidditch assets](https://sketchfab.com/3d-models/quidditch-assets-1bd62f6e20c8414484b9ede6a3458f78), licensed under [CC Attribution](https://creativecommons.org/licenses/by/4.0/)



## Tasks
- [ ] Debug MR alignment - get posts locked-in
- [ ] Sometimes the home orientation is slightly off
- [ ] Add proportional force to barrier repulsion (currently just integral)
- [ ] Drones hit intermediate waypoint early on landing
- [ ] Set TKL points in-game - send in local coordinates, UAV will convert to GPS
- [ ] Auto-assign team based on location relative to drone-cage
- [ ] Quaffle spawn mechanics
- [ ] Only connect to ROS if server
- [ ] Server IP parameter in-game - somehow adjust ROSIntegration to not autoconnect at start
- [ ] package into binary
- [ ] situational awareness
  - [ ] arrow indicators
  - [ ] minimap
  - [ ] collision notification
- [ ] code architecture diagrams
- [ ] segregate field halves so drone can only be on their own team's half
- [ ] use USB IDs or something to match up video receivers with the correct player assignments
- [ ] Fix Quaffle mesh so origin is in center of ball
- [ ] Change bludger to separate mesh / texture
- [ ] Cooldown loading indicator for quaffle and bludger
- [ ] Software architecture diagram
- [ ] explanation of game state, mode, etc.
