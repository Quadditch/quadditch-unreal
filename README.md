
You'll need unreal engine 4.25 and Visual Studio 2019 to develop. Most work can be done in the unreal engine editor on the blueprints, but some things (especially the ROSIntegration stuff)
need to be done in VS. If something seems overcomplicated or suboptimal, chances are I had to do it that way to get things working. It could also be that this was my first UE project and I
didn't know how to do something the "right" way.


### Licensed content required:
[Quadcopters](https://unrealengine.com/marketplace/en-US/product/quadcopters) package. When you add the files back in don't forget to remove the gitignores. Add the following file structure

Content/Quadcopters/
&emsp;    /Cue
&emsp;&emsp;        /SC_QuadcoptersAudio.uasset
&emsp;    /Materials
&emsp;&emsp;        /Inner_Collision.uasset
&emsp;&emsp;        /M_QuadcopterA_Master_01.uasset
&emsp;&emsp;        /M_QuadcopterA_Master_02.uasset
&emsp;&emsp;        /MI_QuadcopterA_01.uasset
&emsp;&emsp;        /MI_QuadcopterA_02.uasset
&emsp;&emsp;        /MI_QuadcopterA_03.uasset
&emsp;&emsp;        /MI_QuadcopterA_04_BLUE.uasset
&emsp;&emsp;        /Outer_Collision.uasset
&emsp;    /Mesh
&emsp;&emsp;        /SM_QuadcopterA_Cam.uasset
&emsp;&emsp;        /SM_QuadcopterA_Main.uasset
&emsp;&emsp;        /SM_QuadcopterA_Rotor.uasset
&emsp;    /Textures
&emsp;&emsp;        /T_QuadcopterA_BC_01.uasset
&emsp;&emsp;        /T_QuadcopterA_BC_02.uasset
&emsp;&emsp;        /T_QuadcopterA_M_01.uasset
&emsp;&emsp;        /T_QuadcopterA_M_02.uasset
&emsp;&emsp;        /T_QuadcopterA_M_03.uasset
&emsp;&emsp;        /T_QuadcopterA_M_04.uasset
&emsp;&emsp;        /T_QuadcopterA_N.uasset
&emsp;    /Wav
&emsp;&emsp;        /S_QuadcoptersAudio.uasset



### Things to change before running:
- In ROS game instance, change IP/Port to your ROS machine

Ideally for things like takeoff and landing we would use ROS actions to robustly and flexibly handle things like takeoff. Unfortunately the ROSIntegration plugin for UE4 does not support actions.
Alternatively we could use services and have the drone respond whenever it is done with the task. Unfortunately the ROSIntegration plugin does not support services running for longer than five seconds.
What we have to do is run a service to let the drone know to take off, and the response is simply an ack. Then the drone will use a different service to let us know it finished.
I initially did this with messages but sometimes they get dropped and I didn't want to deal with the extra complexity of all the acks going back and forth.



### Trouble building (missing symbols about topic / service conversion)?

1. Delete sln/intermediate/saved/binaries\
1. Use bat file to rebuild ROSIntegration plugin
1. generate visual studio files (to make new sln)
1. build again
