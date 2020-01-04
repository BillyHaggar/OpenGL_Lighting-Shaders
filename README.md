## MODEL LOADER PLUS  

This is all about the `MODEL LOADER PLUS`
Model Loader Plus is based on the original previous project of `MODEL LOADER`, all of which commits and previous work has been cloned over into this repository. As said the starting point of this project was to improve the original `MODEL LOADER` by implementing more advanced features such as Advanced Lighting, Bloom and Shadows as well as a GUI for editing aspects of the shaders. All of the mentioned is implemented within this project. See Below for a More under the hood look into how all of this works.
  

## How to Run
[![](http://img.youtube.com/vi/P8T7DuKGDec/0.jpg)](http://www.youtube.com/watch?v=P8T7DuKGDec "How to Run Software in VS 2017")

- Click on the video above to view a walkthrough of running this project.
- Run in release mode in VS 2017, with toolset v141 and windows SDK 10.0.17763.0.
- Must be run in release in order for Regex to run at an appropriate speed (very long delays otherwise).
- When opening up the soloution the solution should just run as nuget packages are used for other header files and packages.
- When upgradeing to VS 2019 as well as upgrading the SDK version problems can occur with running.


## Current Functionality

 - .obj and dae files can loaded and rendered
 - Textures applied (UPDATED)
 - Colours added from files
 - Lighting applied using UVS/Normals (UPDATED)
 - Multiple objects in render space possible
 - Objects can be deleted from render space
 - Textures can be swapped
 - Appropriate memoroy management applied (UPDATED)
 - Larger files can be rendered
 - Objects can be Chosed to be rendered
 - wireframes can be viewed (UPDATED)
 - light source is moveable (UPDATED)
 - Blinn-Phong Lighting Implemented (NEW)
 - GUI using ImGui implemented (NEW)
 - Shadows are now implemented (NEW)
 - Bloom is Implemented (NEW)
 
 
## On Program Run (What to do once program has started to be run)

- The console will open and print out what is being done while the window is being prepared
- Once everything is initialised a window will open and you will be greeted with a world consisting of a flat plane grid and 7 objects, 6 cubes and a boat object.
- The `Model Loader` window will now run and the controls below will control the software.
- Within the program, effects such as BLoom, Shadows and lighting will be demonstrated. By using the GUI windows effects can be turned on or off as well as tweaked to look how the user would like them. Controls below as well as the video explaining the program functionality further down below explains these gui windows further.


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

#### IMGUI Windows
All windows will require mouse control to be visible, press <kbd>1</kbd> in order to toggle the mouse on or off.
##### MAIN WINDOW
  - Here in the main window settings the ambient light level can be adjusted with the slider.
  - To change the light colour either click on the light colour box to pick a new colour or use the R,G,B sliders to fine tune the RGB value of the light.
  - Pressing the `Teleport light to me` button will do as said, it teleports the light to just above the camera position.
  - By toggling `Show Camera Settings` the Camera Settings Window will open.
  - By toggling `Show Feature Buttons` the Feature Buttons window will open.
  - Framerate is displayed at the bottom of this window.
  
 ##### CAMERA SETTINGS wINDOW
  - Here you can change camera settings such as camera speed and mouse sensitivity.
  - By moving the sliders up or down you can increase their retrospective setting.
 
 ##### Feature Buttons Window
  - Here you can toggle bloom on or off, as well as access the toggle features mentioned above which are toggled with the keyboard keys.
  - By pressing the buttons these act as if you were pressing the relating keyboard key.
  - The Checkbox for bloom will toggle the bloom effect on or off
  
  To close any new window press the `close me` button. 
  For a more in depth look into how these windows work view the video below on the use of this program.
  
  ## Using the Software (A Video Walkthrough)
  [![](http://img.youtube.com/vi/P8T7DuKGDec/0.jpg)](http://www.youtube.com/watch?v=P8T7DuKGDec "Model Loader Plus")

## How the Code Runs (What does what)
#### Start of program flow
Everything in the software starts from main, all includes at the top are related to packages and custom classes (header files) needed in order to run this software.
 
 
## What Makes This Project
#### What this project started with

#### Whats unique

#### What works well
Whats good about this project is the lighting as a whole, the shadows, bloom, blinn-phone lighting and how all this works together. With all these together you get a higher realism of lighting closer to AAA games and an understanding of how further development could get closer to a AAA game.



