# core_generating_network_windows
This is the next version of the project non backpropagation neural network which includes considerable changes and improvements.

This is a novel ML algorithm which uses LP for generating a trained neural network.
Version 1 (non backpropagation neural network) had certain shortcommings like poor accuracy in data which has large no os attributes. Also it did not had 
any mechanism to to fine tune the hyper parameters. 

This version solves all such problems.

This implementation for windows is a bit inferior to the linux version in terms of performance and resource utilization. The linux version used much less RAM.
The plus point of the windows version is both gui and command line version is included. Linux version do not have any gui version.

Copyrighte Yuvraj Talukdar SW-16114/2023


Compilation from source (Windows command line edition)-
Required Library
1. mingw-64 compiler which supports c++ std 17. Get the compiler from msys and save yourself the hassel.   
2. Make
For compilation-
1. Git clone https://github.com/YuvrajTalukdar/core_generating_network_windows.git
2. cd core_generating_network_windows
3. make all
4. To run- ./a.exe
For Compilation from source for Linux go to- https://github.com/YuvrajTalukdar/core_generating_network

Compilation from source (Windows gui line edition)-
Required tools/libraries
1. QT Creator along with the qt environment configured for mingw-64 compiler.
2. Open the dir core_generating_network_windows/cgn_gui_windows/
3. Build the software from qt creator.
