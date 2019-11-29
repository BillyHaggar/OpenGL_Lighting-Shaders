## MODEL LOADER  

This is all about the `MODEL LOADER`
  

## How to Run

- run in release mode in vs 2017 toolset v141
- must be release in order for Regex to run at an appropriate speed



## Current Functionality

 - .obj files are loaded
 - 4 .obj based objects are loaded and rendered
 - lighting implemented
 - Camera implemented
 - Meshes implemented
 - Dae files can be loaded
 - 

## CONTROLS
###### Camera 

- moving the mouse around will move around the x and y axis of whare the camera is pointing

W key
- move towards where the camera is pointing

S key
- move away from where the camera is pointing

A key
- straife left

D key
- straife right

space key
- move camera up on z axis (increase height)

Left Shift key
- move camera down on z axis (decrease height)

###### Enable Features
1 key
- Toggle mouse visibility on/off

2 key
- Toggle wire-frame visibility for objects on/off

3 key
- Toggle whether the camera follows the camera or stays still on/off

4 key
- Remove object from being rendered (Will remove objects in reverse loaded order down to a minimum of 3 objects)

5 Key 
- Swap textures on all objects

## Development Process
#### Beginnings 
 When starting development heavy use of LearnOpenGL code was used, then at later stages such as the parser, independant c++ knowledge was used as well as research into each of the file types.

#### Main Development
 Later in development after the main set up for rendering was achieved more advanced features were implemented, these features were items such as lighting, DAE implemntation, multiple objects loaded as well as removing these objects.

#### Later Features
 Some later features can be added, these are hit box detection, advanced lighting such as bloom as well as a better way for the console to load in objects.
