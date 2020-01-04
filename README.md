## MODEL LOADER  

This is all about the `MODEL LOADER`
Model Loader is an application that will currently load .Obj and .dae files and render them in a space in the world. These objects currently have lighting, colour and textures applied to them. Please see below for futher details on running and controls.
  

## How to Run
[![](http://img.youtube.com/vi/P8T7DuKGDec/0.jpg)](http://www.youtube.com/watch?v=P8T7DuKGDec "How to Run Software in VS 2017")

- Run in release mode in VS 2017, with toolset v141 and windows SDK 10.0.17763.0
- Must be run in release in order for Regex to run at an appropriate speed (very long delays otherwise)
- When opening up the soloution the solution should just run as nuget packages are used for other header files and packages.
- When upgradeing to VS 2019 as well as upgrading the SDK version problems can occur with running.


## Current Functionality

 - .obj and dae files are loaded and renderered
 - Textures applied
 - Colours added from files
 - Lighting applied using UVS/Normals
 - Multiple objects in render space possible
 - Objects can be deleted from render space
 - Textures can be swapped
 - Appropriate memoroy management applied 
 - Larger files can be rendered
 - objects can be selected
 - see below for more information

## On Program Run

- The console will open and load 4 objects into memory
- These objects will be the Creeper.obj, low_poly_boat.obj , pouf.obj and custom.obj
- To load a custom obj replace the custom obj files loacted in the media folder within the model loader files.
- Make sure to not rename the folder and replate the mtl and obj file with the custom files (make sure they are saved witht the same names)
- When these 4 objects are loaded input is requested from the user
- By typing 'Exit' the program will not load any extra objs
- otherwise type either ''Creeper', 'Boat', 'Pouf', 'Custom' to load the relating obj model
- PLEASE REMEMBER THESE ARE CASE SENSITIVE
- Maximum number of objects that can be selected is 7, including the 4 that are automatically loaded.
- After selection or by typing 'Exit' the Low_poly_boat.dae will load in.
- The `Model Loader` window will now run and the controls below will control the software.


## CONTROLS
#### Camera 

- Moving the mouse around will move around the x and y axis of whare the camera is pointing
- To move towards where the camera is pointing/ forwards, press <kbd>w</kbd>
- To move away from where the camera is pointing/ backwards, press <kbd>s</kbd>
- To move the camera left, press <kbd>a</kbd>
- To move the camera right, press <kbd>d</kbd>
- To move camera up on z axis (increase height), press <kbd>space</kbd>
- To move camera down on z axis (decrease height), press <kbd>LeftShift</kbd>

#### Enable Features
- Toggle mouse visibility on/off, press <kbd>1</kbd>
- Toggle wire-frame visibility for objects on/off, press <kbd>2</kbd>
- Toggle whether the light follows the camera or stays still on/off, press <kbd>3</kbd>
- Remove object from being rendered (Will remove objects in reverse loaded order down to a minimum of 3 objects), press <kbd>4</kbd>
- Swap textures on all objects <kbd>5</kbd>
- To close the program press <kbd>esc</kbd>

## Development Process
#### Beginnings 
 When starting development heavy use of LearnOpenGL code was used, then at later stages such as the parser, independant c++ knowledge was used as well as research into each of the file types. Research was vital in order to complete this project as a strong understanding of C++ coding as well as how game objects rendered was necessary. Sprinkle in more OpenGL research and knowledge and this is how development could really start.

#### Main Development
  In Main developmen,t after the main set up for rendering was achieved, more advanced features were implemented, these features were items such as lighting, DAE implemntation, multiple objects loaded as well as removing objects. 

#### Later Features
 Some later features can be added, these are hit box detection, advanced lighting such as bloom as well as a better way for the console to load in objects. Overall however, with the knowledge known now a decent refractor of the code can occur, as well as deleteing unused code and clearing repeated code.
