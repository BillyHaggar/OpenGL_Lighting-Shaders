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
///own header files
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Loader.h"
///c++ libraries
#include <iostream>
#include <vector>

using namespace std;
/*--------------------- SETTINGS AND GLOBAL VARIABLES ---------------------------------------------------------------------*/
///Settings____________________________________________________
//set the window height and width here
const unsigned int windowWidth = 1600; // default value 1600 width
const unsigned int windowHeight = 1200; // default value 1200 width

///buffers__________________________________________________
unsigned int VBO, VAO, EBO, lightVAO, lightVBO;

///object data______________________________________________
std::vector <float> object;
std::vector <int> indices;

///object origin posistions
glm::vec3 objectPositions[10] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

///Textures______________________________________________________
unsigned int texture;
int textureWidth, textureHeight, nrChannels;
unsigned char *textureData;

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
glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);

///object creators_______________________________________________
Camera camera;
Material material;
Loader loader;

///other variables ____________________________________________________
//declare the locations for the mouse location
//Initialise with the original location of the centre of the window
float lastX = windowWidth / 2;
float lastY = windowHeight / 2;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

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

///initialize the buffers and assign data to them
void buffersInit() {
	//Main object VAO, VBO, EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind the object/s VAO/VBO ready to assign object data to them
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//vertex coordinates offsets and locations
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal coordinates offsets and locations
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//texture coordinates offsets and locations
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//Bind data to the buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, object.size() * sizeof(float), &object[0], GL_STATIC_DRAW);
}
///_________________________________________________________________________________________________End of function

///texture handler
//deal with generating and creating textures ready for the shaders to use
void textureInit() {
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	//read the data from file
	textureData = stbi_load(".\\Creeper-obj\\Texture.png", &textureWidth, &textureHeight, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//create the texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	//same for the generation of mipMaps
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData); // clear up the data now we dont need it

}
///_________________________________________________________________________________________________End of function

///create qnd fill the VAO, VBO for the light object
void lightInit() {
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	
	glBindVertexArray(lightVAO); // bind this new VAO
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	
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

	float sensitivity = 0.09f;
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
///_________________________________________________________________________________________________End of function

///Input handler
// Basic function to check for inputs
void processInput(GLFWwindow *window) {

	float cameraSpeed = 4.5f * deltaTime;
	//check for the escape key and check if its been pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // if true close window
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.cameraPos -= cameraSpeed * camera.cameraUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.cameraPos += cameraSpeed * camera.cameraUp;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.cameraPos += cameraSpeed * camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.cameraPos -= cameraSpeed * camera.cameraFront;;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.cameraPos += glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		lightPosition = camera.cameraPos;
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
	glfwMakeContextCurrent(window); //target window of open gl we created
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // create call back to for window resize
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glewInit(); // initialise glew componenets
}
///_________________________________________________________________________________________________End of function

///main program run
int main() {
	cout << "Program Running..." << endl;
	cout << "Press escape to close software..." << endl << endl;
	
	loader.loadOBJ(".\\Creeper-obj\\Creeper.obj");
	loader.objectBuilder(object, indices);
	material.loadMTL(".\\Creeper-obj\\Creeper.mtl", material);
	init();
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Model_Loader", NULL, NULL);;
	windowInit(window);

	//create the shaders needed using the shader header to create the vertex and the fragment shader
	Shader objectShaders("mainVertex.vs", "mainFragment.fs");
	Shader lightShaders("lightVertex.vs", "lightFragment.fs");

	//further Inits
	buffersInit();
	textureInit();
	lightInit();

	objectShaders.run(); // don't forget to activate the shader before setting uniforms!  
	objectShaders.setInt("texture", 0);
	objectShaders.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	objectShaders.setFloat("ambientLight", 0.2f);
	setMTL(objectShaders, material);

	glEnable(GL_DEPTH_TEST);
	//Main drawing loop, effectivly what will happen evey frame (easy way to think about it)

	while (!glfwWindowShouldClose(window)) {
		//calulate time between frames
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		processInput(window);// the key checks above for the escape key to close the window (own version)

		glClearColor(0.15f, 0.15f, 0.15f, 0.3f); //set background render colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the colour buffer

		//activate and bind the textures we are using
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//set up the main shaders and bind ready to render
		objectShaders.run();
		objectShaders.setVec3("viewPosition", camera.cameraPos);
		objectShaders.setVec3("lightPos", lightPosition);	
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.fov), (float)windowWidth / (float)windowHeight, 0.1f, 300.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
		objectShaders.setMat4("projection", projectionMatrix);
		objectShaders.setMat4("view", viewMatrix);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//repeate for abount of objects
		for (int i = 0; i < 1; i++) {
			//change the model matrix for each object
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, objectPositions[i]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.09f));
			modelMatrix = glm::rotate(modelMatrix, /*(float)glfwGetTime()/4*/glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
			objectShaders.setMat4("model", modelMatrix);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}

		//draw the light cube
		lightShaders.run();
		lightShaders.setMat4("projection", projectionMatrix);
		lightShaders.setMat4("view", viewMatrix);
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f)); // a smaller cube
		lightShaders.setMat4("model", modelMatrix);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window); //another buffer for rendering
		glfwPollEvents(); // Deals with pollling events such as key events
	}

	//de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	glDeleteBuffers(1, &EBO);

	//clean up and close down correctly
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;//return 0, exited normally
}
///_________________________________________________________________________________________________End of function