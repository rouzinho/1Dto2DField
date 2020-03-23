# Tranform a 1 Dimensional Field

This Cedar plugin transform a 1Dimensional field to a 2D one

Everything you want to know about DFT -> https://dynamicfieldtheory.org/

Cedar is the C++ Framework implementing the concepts of DFT -> https://cedar.ini.rub.de/

## Getting Started

The plugin is a widget that transform a 1Dimensional Field into a 2D one. If the 1D field had a size 1x100, the 2D output would be a 10x10 field. 

The code work for the 6.x version of Cedar.


### Prerequisites

You first need to install cedar by following the instructions here : https://cedar.ini.rub.de/tutorials/installing_and_running_cedar/

You can't use a precompiled version of Cedar to compile and run the plugin.

I suggest reading about how to create a plugin in Cedar first, it will greatly help to understand how it works : https://cedar.ini.rub.de/tutorials/writing_custom_code_for_cedar/

### Installing

First clone the repository :

`https://github.com/rouzinho/1Dto2DField.git`

In the project.conf, change the CEDAR_HOME directory to your own :

`set(CEDAR_HOME "your_own_cedar_repository")`

Then create a build repository and prepare the environment for the compilation :

`mkdir build`

`cd build`

`cmake ..`

Finally start the compilation :

`make`

You should see the plugin under the name libOneDimTwoDim.so in the build/ repository

## Run the plugin

Execute cedar and load it into cedar 

*Tools -> Manage plugins*

In the plugin Manager window, click on *add* and choose the plugin libOneDimTwoDim.so (located in build/). This one should appear in the window.

You can close the window. The plugin is loaded inside cedar.

You can now go back to the cedar main interface and click on the Utilities tab.

Drag the widget into the architecture panel. Connect a 1 Dimensional Field to the input and connect the ouput to a 2Dimensional field.

## Authors

Quentin Houbre - Tampere University

## License

This project is licensed under the BSD licence


