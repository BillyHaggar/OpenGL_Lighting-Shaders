///image stb_image.h loader
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
///openGL Libraries
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
///imgui header files
#include "Media/Imgui/imgui.h"
#include "Media/Imgui/imgui_impl_glfw_gl3.h"
///own header files
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Loader.h"
#include "Mesh.h"
///c++ libraries
#include <iostream>
#include <vector>

using namespace std;
/*--------------------- SETTINGS AND GLOBAL VARIABLES ---------------------------------------------------------------------*/
///Settings____________________________________________________
//set the window height and width here
const unsigned int windowWidth = 1600; // default value 1600 width
const unsigned int windowHeight = 1200; // default value 1200 widtH

///buffers__________________________________________________
unsigned int light_VAO, light_VBO;

///object origin posistions
glm::vec3 objectPositions[8] = {
  glm::vec3(0.0f,  -30.0f,  0.0f),
  glm::vec3(100.0f,  25.0f, -70.0f),
  glm::vec3(215.0f, 40.0f, -150.0f),
  glm::vec3(240.0f, 10.0f, -100.0f),
  glm::vec3(170.0f, 35.0f, -175.0f),
  glm::vec3(130.0f, 50.0f, -40.0f),
  glm::vec3(80.0f, 15.0f, -240.0f),
  glm::vec3(280.0f, 64.0f, -25.0f),
};

///light data_________________________________________________
float lightCube[36*3] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
};
glm::vec3 lightPosition(100.0, 35.0, 110.0);

///object creators_______________________________________________
Camera camera;
bool wireframe = false;
bool mouse = false;
bool lightFollow = false;
Material material;
Loader loader;
std::vector<Mesh> objects;

struct objectPaths {
	string name;
	const char * objectPath;
	const char * mtlPath;
	const char * basePath;
}creeper, boat, pouf, custom, grid;


///other variables ____________________________________________________
//declare the locations for the mouse location
//Initialise with the original location of the centre of the window
float lastX = windowWidth / 2;
float lastY = windowHeight / 2;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

///ImGUI variables
bool showMainWindow = true;
bool showCameraWindow = false;
bool showFeaturesWindow = false;
static glm::vec3 lightColor(1.0f);
static float ambientLight = 0.2f;
static float cameraSpeedMultiplier = 1.0f;
static float mouseSensitivity = 1.0f;

/*-------------------- FUNCTIONS -------------------------------------------------------------------------------------------*/
///OpenGl packages all initialisations
void init() {
	//intialise the required GLFW things
	glewExperimental = GL_TRUE; //needed for some reason unknown
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
///_________________________________________________________________________________________________End of function

///init object structs
void initObjectPaths() {
	creeper.name = "Creeper";
	creeper.objectPath = "Media\\Objects\\Creeper-obj\\Creeper.obj";
	creeper.mtlPath = "Media\\Objects\\Creeper-obj\\Creeper.mtl";
	creeper.basePath = "Media\\Objects\\Creeper-obj\\";

	boat.name = "Boat";
	boat.objectPath = "Media\\Objects\\LowPolyBoat-obj\\Low_Poly_Boat.obj";
	boat.mtlPath = "Media\\Objects\\LowPolyBoat-obj\\Low_Poly_Boat.mtl";
	boat.basePath = "Media\\Objects\\LowPolyBoat-obj\\";

	pouf.name = "Pouf";
	pouf.objectPath = "Media\\Objects\\Pouf-obj\\Pouf.obj";
	pouf.mtlPath = "Media\\Objects\\Pouf-obj\\Pouf.mtl";
	pouf.basePath = "Media\\Objects\\Pouf-obj\\";

	custom.name = "Custom";
	custom.objectPath = "Media\\Objects\\Custom-obj\\Custom.obj";
	custom.mtlPath = "Media\\Objects\\Custom-obj\\Custom.mtl";
	custom.basePath = "Media\\Objects\\Custom-obj\\";

	grid.name = "Grid";
	grid.objectPath = "Media\\Objects\\Grid-obj\\Grid.obj";
	grid.mtlPath = "Media\\Objects\\Grid-obj\\Grid.mtl";
	grid.basePath = "Media\\Objects\\Grid-obj\\";
}
///_________________________________________________________________________________________________End of function


///create qnd fill the creeper_VAO, creeper_VBO for the light object
void lightInit() {
	glGenVertexArrays(1, &light_VAO);
	glGenBuffers(1, &light_VBO);
	
	glBindVertexArray(light_VAO); // bind this new creeper_VAO
	glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightCube), lightCube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
///_________________________________________________________________________________________________End of function

///viewport handler
//deal with window resizes and edit the render space
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	//reset the mouse posisions when going full screen or window size change
	lastX = width / 2;
	lastY = height / 2;
}
///_________________________________________________________________________________________________End of function

///Mouse callback hander function
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouse) {
		//stop mouse jumping around when first detecting mouse
		if (camera.firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			camera.firstMouse = false;
		}

		float xOffset = xpos - lastX;
		float yOffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.09f * mouseSensitivity;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		camera.yaw += xOffset;
		camera.pitch += yOffset;

		//stop the mouse looping round the z axis, can only go as high as the sky and the floor
		if (camera.pitch < -89.0f)
			camera.pitch = -89.0;
		if (camera.pitch > 89.0f)
			camera.pitch = 89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
		front.y = sin(glm::radians(camera.pitch));
		front.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));

		camera.cameraFront = glm::normalize(front);
	}
}
///_________________________________________________________________________________________________End of function

///Key callback for keypresses we dont want to be repeated
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
		mouse = !mouse;
		camera.firstMouse = true;
		mouse ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
		wireframe = !wireframe;
		wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);;
	}
	if (key == GLFW_KEY_3 && action == GLFW_RELEASE)
		lightFollow = !lightFollow;
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE && objects.size() > 3) { //only allow to go down to 3
		objects.erase(objects.begin() + (objects.size() - 1)); // better than pop back, will clear the allocated memory too!
	}
	if (key == GLFW_KEY_5 && action == GLFW_RELEASE){
		for (int i = 0; i < objects.size(); i++) {
		objects.at(i).swapTexture();
		}
	}
}
///_________________________________________________________________________________________________End of function

///Input handler for movement
// Basic function to check for inputs
void processInput(GLFWwindow *window) {

	float cameraSpeed = (30.0f * cameraSpeedMultiplier) * deltaTime;
	//check for the escape key and check if its been pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // if true close window
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.cameraPos -= cameraSpeed * camera.cameraUp;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.cameraPos += cameraSpeed * camera.cameraUp;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.cameraPos += cameraSpeed * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.cameraPos -= cameraSpeed * camera.cameraFront;;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
}
///_________________________________________________________________________________________________End of function

///set MTL to the shaders
void setMTL(Shader &shader, Material &mat) {
	shader.setFloat("material.Ns", mat.Ns);
	shader.setVec3("material.Ka", mat.Ka);
	shader.setVec3("material.Kd", mat.Kd);
	shader.setVec3("material.Ks", mat.Ks);
	shader.setVec3("material.Ke", mat.Ke);
	shader.setFloat("material.Ni", mat.Ni);
	shader.setFloat("material.d", mat.d);
	shader.setInt("material.illum", mat.illum);
}
///_________________________________________________________________________________________________End of Function

///initialize the window
int windowInit(GLFWwindow* window) {
	//create the window and check to see if the window opened correctly, if not terminate glfw and return error data
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	//init GUI
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glfwMakeContextCurrent(window); //target window of open gl we created
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // create call back to for window resize
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glewInit(); // initialise glew componenets


	return 0;
}
///_________________________________________________________________________________________________End of function

/// load an obj object, call all functions and create the mesh needed to run the object
void loadObjects(const char * objPath, const char * mtlPath, float scale) {
	Loader loaderTemp;
	std::vector <float> objectTemp;
	std::vector <int> indicesTemp;
	std::vector<Material> materialsTemp;
	loaderTemp.loadOBJ(objPath);
	loaderTemp.loadMTL(mtlPath, materialsTemp);
	loaderTemp.objectBuilder(objectTemp, indicesTemp, materialsTemp);
	Mesh tempMesh(objectTemp, indicesTemp, loaderTemp.hasTexture, scale);
	objects.push_back(tempMesh);
}
///_________________________________________________________________________________________________End of function

///Load Dae Object
void loadObjectsDAE(const char * daePath, float scale) {
	Loader tempLoader;
	std::vector <float> objectTempDAE;
	std::vector <int> indicesTempDAE;
	tempLoader.loadDAE(daePath, objectTempDAE, indicesTempDAE);
	Mesh tempMesh(objectTempDAE, indicesTempDAE, tempLoader.hasTexture, scale);
	objects.push_back(tempMesh);
}
///_________________________________________________________________________________________________End of function

///take input from user on what additional objects to load.
void chooseObjects() {
	if (objects.size() >= 7) {
		cout << "MAXIMUM OBJECTS REACHED!!" << endl << endl;
		return;
	}

	cout << "Would you like to Select Another Object to Render?" << endl;
	cout << "Please enter 'Exit' for No, otherwise select an object below to render..." << endl << endl;
	string x;

		cout << "Please select by typing either 'Creeper' : 'Boat' : 'Pouf' : 'Custom' " << endl << endl;
		cin >> x;
		cout << endl;
		if (x == creeper.name) {
			loadObjects(creeper.objectPath, creeper.mtlPath, 40.0f);
			chooseObjects();
		} 
		else if (x == boat.name) {
			loadObjects(boat.objectPath, boat.mtlPath, 0.3f);
			chooseObjects();
		}
		else if (x == pouf.name) {
			loadObjects(pouf.objectPath, pouf.mtlPath, 60.0f);
			chooseObjects();
		}
		else if (x == custom.name) {
			loadObjects(custom.objectPath, custom.mtlPath, 0.3f);
			chooseObjects();
		}
		else if (x == "Exit") {
			return; //do nothing
		}
		else {
			cout << "INVALID SELECTION: CHECK CASE?" << endl << endl;
			chooseObjects();
		}
}
///_________________________________________________________________________________________________End of function

///create the windows and options they will change
void renderGui(GLFWwindow *window) {

	//Main ImGui Window
	ImGui::Begin("Main Settings", &showMainWindow);
	ImGui::Text("Edit Settings in this here window!!\n\n");
	ImGui::Text("-----------------------------");
	ImGui::Text("Lighting Settings");
	ImGui::Text(" ");
	ImGui::SliderFloat(" Ambient Light Level", &ambientLight, 0.0f, 1.0f);
	ImGui::ColorEdit3(" Light Colour", (float*)&lightColor);
	if (ImGui::Button("Teleport light to me"))
		lightPosition = camera.cameraPos + glm::vec3(0.0f, 8.0f, 0.0f);
	ImGui::Text("-----------------------------");
	ImGui::Checkbox(" Show Camera Settings\n", &showCameraWindow);
	ImGui::Text("-----------------------------");
	ImGui::Checkbox(" Show Feature Buttons\n", &showFeaturesWindow);
	ImGui::Text("-----------------------------");
	ImGui::Text("FRAMERATE");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	if (showCameraWindow)
	{
		ImGui::Begin("Camera Settings", &showCameraWindow);
		ImGui::Text("Edit Camera Settings in this here window!!\n\n");
		ImGui::Text("-------------------------------------------------");
		ImGui::SliderFloat(" Camera Speed Multiplier", &cameraSpeedMultiplier, 0.0f, 5.0f);
		ImGui::SliderFloat(" Mouse Sensitivity", &mouseSensitivity, 0.0f, 5.0f);

		if (ImGui::Button("Close Me"))
			showCameraWindow = false;
		ImGui::End();
	}

	if (showFeaturesWindow)
	{
		ImGui::Begin("Features Settings", &showFeaturesWindow);
		ImGui::Text("Toggle Features on and off here!!\n\n");
		ImGui::Text("-------------------------------------------------");

		if (ImGui::Button("1: Regain Camera Mouse Control")) {
			mouse = !mouse;
			camera.firstMouse = true;
			mouse ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		if (ImGui::Button("2: Toggle WireFrames")) {
			wireframe = !wireframe;
			wireframe ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);;
		}

		if (ImGui::Button("3: Toggle Light Following Camera"))
			lightFollow = !lightFollow;

		if (ImGui::Button("4: Remove a Rendered Object")) {
			if (objects.size() > 3) {
				objects.erase(objects.begin() + (objects.size() - 1));
			}
		}

		if (ImGui::Button("5: Toggle Textures")) {
			for (int i = 0; i < objects.size(); i++) {
				objects.at(i).swapTexture();
			}
		}

		if (ImGui::Button("Close Me"))
			showFeaturesWindow = false;
		ImGui::End();
	}

	//draw the GUI
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}
///_________________________________________________________________________________________________End of function

///Bloom, and what is needed for that bloomy goodness (This should probably be in its own header and cpp but we will sort that 
/// out later)
//Variables needed
unsigned int hdrFBO;
unsigned int colorBuffers[2];
unsigned int rboDepth;
unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
unsigned int pingpongFBO[2];
unsigned int pingpongColorbuffers[2];
//Function
void bloomEffect() {
	//gen the HDR frame buffer
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

	glGenTextures(2, colorBuffers);

	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGB16F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		// attach texture to framebuffer
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
		);
	}

	//gen the depth buffer
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	
	//attach and draw both buffers
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		
		// also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
}
///_________________________________________________________________________________________________End of function

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}


///main program run
int main() {
	cout << "Program Running..." << endl;
	cout << "Press escape to close software..." << endl << endl;
	init();
	initObjectPaths();

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Model_Loader", NULL, NULL);
	windowInit(window);

	//load default objects
	loadObjects(grid.objectPath, grid.mtlPath, 20.0f);
	for (int o = 0; o < 7; o++) {
		loadObjects(creeper.objectPath, creeper.mtlPath, 25.0f);
	}
	//loadObjectsDAE("Media\\Objects\\low_poly_boat.dae", 0.3f);
	//loadObjects(pouf.objectPath, pouf.mtlPath, 60.0f);
	//loadObjects(custom.objectPath, custom.mtlPath, 0.3);
	
	//chooseObjects();

	//create the shaders needed using the shader header to create the vertex and the fragment shader
	Shader objectShaders("Media\\Shaders\\mainVertex.vs", "Media\\Shaders\\mainFragment.fs");
	Shader lightShaders("Media\\Shaders\\lightVertex.vs", "Media\\Shaders\\lightFragment.fs");
	Shader blurShaders("blur.vs", "blur.fs");

	lightInit();

	objectShaders.run(); // don't forget to activate the shader before setting uniforms!  
	objectShaders.setInt("texture", 0);
	setMTL(objectShaders, material);

	glfwShowWindow(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);

	bloomEffect();

	//Main drawing loop, effectivly what will happen evey frame (easy way to think about it)
	while (!glfwWindowShouldClose(window)) {
		ImGui_ImplGlfwGL3_NewFrame();//create a new frame for GUI
		
		//calulate time between frames
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		processInput(window);// the key checks above for the escape key to close the window (own version)

		glClearColor(0.25f, 0.25f, 0.35f, 0.3f); //set background render colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the colour buffer


		//set up the main shaders and bind ready to render
		objectShaders.run();
		objectShaders.setVec3("viewPosition", camera.cameraPos);
		objectShaders.setVec3("lightPos", lightPosition);	
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.fov), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
		objectShaders.setMat4("projection", projectionMatrix);
		objectShaders.setMat4("view", viewMatrix);

		//draw grid
		glBindVertexArray(objects.at(0).VAO);
		glBindBuffer(GL_ARRAY_BUFFER, objects.at(0).VBO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, objects.at(0).texture);
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				//change the model matrix for each object
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, (objectPositions[0] + glm::vec3((40.0f * (x + 1)), 0.0f, (-40.0f * y))));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(objects.at(0).scale));
				objectShaders.setMat4("model", modelMatrix);

				glDrawElements(GL_TRIANGLES, objects.at(0).indices.size(), GL_UNSIGNED_INT, 0);
			}
		}

		//repeate for abount of objects
		for (int i = 1; i < objects.size(); i++) {
			glBindVertexArray(objects.at(i).VAO);
			glBindBuffer(GL_ARRAY_BUFFER, objects.at(i).VBO);

			//change the model matrix for each object
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, objectPositions[i]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(objects.at(i).scale));
			float angle = 20.0f * i;
			modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objectShaders.setMat4("model", modelMatrix);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, objects.at(i).texture);

			glDrawElements(GL_TRIANGLES, objects.at(i).indices.size(), GL_UNSIGNED_INT, 0);
		}

		
		if (!lightFollow) {
			//draw the light cube when not following camera, else move light with camera
			lightShaders.run();
			lightShaders.setMat4("projection", projectionMatrix);
			lightShaders.setMat4("view", viewMatrix);
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, lightPosition);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f)); // a smaller cube
			lightShaders.setMat4("model", modelMatrix);
			glBindVertexArray(light_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else {
			lightPosition = glm::vec3(camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z + 5.0f);
		}

		/// test Bloom
		bool horizontal = true, first_iteration = true;
		unsigned int amount = 10;
		blurShaders.run();
		for (unsigned int i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
			blurShaders.setInt("horizontal", horizontal);
			glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
			renderQuad();
			horizontal = !horizontal;
			if (first_iteration)
				first_iteration = false;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//Imgui Gui windows
		renderGui(window);

		objectShaders.run(); // don't forget to activate the shader before setting uniforms!  
		objectShaders.setFloat("ambientLight", ambientLight);
		objectShaders.setVec3("lightColor", lightColor);
		lightShaders.run();
		lightShaders.setVec3("lightColor", lightColor);

		glfwSwapBuffers(window); //another buffer for rendering
		glfwPollEvents(); // Deals with pollling events such as key events
	}

	//de-allocate all resources once they've outlived their purpose:
	for (int i = 0; i < objects.size(); i++) {
		glDeleteVertexArrays(1, &objects.at(i).VAO);
		glDeleteBuffers(1, &objects.at(i).VBO);
		glDeleteBuffers(1, &objects.at(i).EBO);
	}
	glDeleteVertexArrays(1, &light_VAO);
	glDeleteBuffers(1, &light_VBO);

	//clean up and close down correctly
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;//return 0, exited normally
}
///_________________________________________________________________________________________________End of function