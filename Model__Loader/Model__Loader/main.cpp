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
glm::vec3 objectPositions[4] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(75.0f,  0.0f, 0.0f),
  glm::vec3(140.f, 0.0f, 0.0f),
  glm::vec3(210.0f, 0.0f, 0.0f),
};

///scale of objects
float objectScales[4]{
	40.3, 0.3, 60.5, 0.3
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
Material material;
Loader loader;
std::vector<Mesh> objects;

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

///Key callback for keypresses we dont want to be repeated
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_RELEASE && objects.size() > 3)
		objects.pop_back();
}
///_________________________________________________________________________________________________End of function

///Input handler
// Basic function to check for inputs
void processInput(GLFWwindow *window) {

	float cameraSpeed = 30.0f * deltaTime;
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
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		lightPosition = glm::vec3(camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z + 5.0f);
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
	glfwSetKeyCallback(window, key_callback);
	glewInit(); // initialise glew componenets
}
///_________________________________________________________________________________________________End of function

void loadObjects(const char * objPath, const char * mtlPath) {
	Loader loaderTemp;
	std::vector <float> objectTemp;
	std::vector <int> indicesTemp;
	std::vector<Material> materialsTemp;
	loaderTemp.loadOBJ(objPath);
	loaderTemp.loadMTL(mtlPath, materialsTemp);
	loaderTemp.objectBuilder(objectTemp, indicesTemp, materialsTemp);
	Mesh tempMesh(objectTemp, indicesTemp, loaderTemp.hasTexture);
	objects.push_back(tempMesh);
}

///main program run
int main() {
	cout << "Program Running..." << endl;
	cout << "Press escape to close software..." << endl << endl;

	init();

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Model_Loader", NULL, NULL);
	windowInit(window);

	loadObjects("Media\\Objects\\Creeper-obj\\Creeper.obj", "Media\\Objects\\Creeper-obj\\Creeper.mtl");
	loadObjects("Media\\Objects\\LowPolyBoat-obj\\Low_Poly_Boat.obj","Media\\Objects\\LowPolyBoat-obj\\Low_Poly_Boat.mtl");
	loadObjects("Media\\Objects\\pouf-obj\\pouf.obj", "Media\\Objects\\pouf-obj\\pouf.mtl");
	loadObjects("Media\\Objects\\Custom-obj\\Custom.obj", "Media\\Objects\\Custom-obj\\Custom.mtl");

	//create the shaders needed using the shader header to create the vertex and the fragment shader
	Shader objectShaders("Media\\Shaders\\mainVertex.vs", "Media\\Shaders\\mainFragment.fs");
	Shader lightShaders("Media\\Shaders\\lightVertex.vs", "Media\\Shaders\\lightFragment.fs");

	lightInit();

	objectShaders.run(); // don't forget to activate the shader before setting uniforms!  
	objectShaders.setInt("texture", 0);
	objectShaders.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	objectShaders.setFloat("ambientLight", 0.3f);
	setMTL(objectShaders, material);

	glfwShowWindow(window);

	glEnable(GL_DEPTH_TEST);
	//Main drawing loop, effectivly what will happen evey frame (easy way to think about it)
	while (!glfwWindowShouldClose(window)) {
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
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.fov), (float)windowWidth / (float)windowHeight, 0.1f, 300.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
		objectShaders.setMat4("projection", projectionMatrix);
		objectShaders.setMat4("view", viewMatrix);

		//repeate for abount of objects
		for (int i = 0; i < objects.size(); i++) {
			glBindVertexArray(objects.at(i).VAO);
			glBindBuffer(GL_ARRAY_BUFFER, objects.at(i).VBO);

			//change the model matrix for each object
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, objectPositions[i]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(objectScales[i]));
			modelMatrix = glm::rotate(modelMatrix, /*(float)glfwGetTime()/4*/glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
			objectShaders.setMat4("model", modelMatrix);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, objects.at(i).texture);

			glDrawElements(GL_TRIANGLES, objects.at(i).indices.size(), GL_UNSIGNED_INT, 0);
		}

		//draw the light cube
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
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;//return 0, exited normally
}
///_________________________________________________________________________________________________End of function