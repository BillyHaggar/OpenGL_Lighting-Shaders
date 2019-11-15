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


glm::vec3 lightPosition(3.0f, 2.0f, 2.0f);

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

//temp loaded object data
std::vector < glm::vec3 > vertices; //vector point for the object
std::vector < glm::vec2 > textureCoords; // texture coordinates for the object
std::vector < glm::vec3 > normals;	// normal coordinates for the object
std::vector < int > vectorIndex, textureIndex, normalIndex; //each vertices element index ((element.at(index) - 1) == index to link to above)
int numOfFaces = 0; //total number of faces for the object
std::vector < bool > faceQuad; //for each face there needs to be a specification if that face is a quad or a tri so it can be converted accordingly

std::vector <float> object;
std::vector <int> indices;

///Textures______________________________________________________
unsigned int textureWall;
unsigned int textureFace;
//texture parameters
int textureWidth, textureHeight, nrChannels;
//texture data stream when for when reading a image file with stb_library
unsigned char *textureData;
/*---------------------------------------------------------------------------------------------------------------------------*/



///Camera variables to be used by the view matrix
//initial stating location of the camera
glm::vec3 cameraPos = glm::vec3(0.5f, 0.5f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

//initial variables of the x,y,z coodinates of the camera pointing direction
//remember that this is acheived by actually mving everything to give the illusion of camera movement
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

//declare the locations for the mouse location
//Initialise with the original location of the centre of the window
float lastX = windowWidth / 2;
float lastY = windowHeight / 2;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//mouse variables, used to know where the camer is pointing, initail variables set the starting location
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 60.0f; //starting FOV, can be used to give the illusion of zooming in by decreasing (45.0f is a good basis to start)


/*-------------------- FUNCTIONS -------------------------------------------------------------------------------------------*/
///initialize the shaders and what they will be processing from the verticies and indicies
void shadersInit() {
	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}
///_________________________________________________________________________________________________End of function

///initialize the triangle required functions, CREATE THE BUFFERS NEEDED FOR RENDERING triangles (VERTICIES AND INDICES)
void triangleInit() {
	// generate the vertex array object
	glGenVertexArrays(1, &VAO);
	//generate the buffers
	glGenBuffers(1, &VBO);
	// generate the EBO for sharing points
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//bind the vertex array
	glBindVertexArray(VAO);
	//Bind the buffers
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//call the buffers and assign the triangles points to the buff-
	//-er, what we are binding, size in data we want to allocate, the data to send to buff-
	//-er how we want the GPU to manage (how often the data will change))
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, object.size() * sizeof(float), &object[0], GL_STATIC_DRAW);
}
///_________________________________________________________________________________________________End of function

///texture handler
//deal with generating and creating textures ready for the shaders to use
void textureInit() {
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	//read the data from file
	textureData = stbi_load(".\\Creeper-obj\\Texture.png", &textureWidth, &textureHeight, &nrChannels, 0);
	glGenTextures(1, &textureFace);
	glBindTexture(GL_TEXTURE_2D, textureFace);
	//create the texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	//same for the generation of mipMaps
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData); // clear up the data now we dont need it

}
///_________________________________________________________________________________________________End of function


///create and initialize all things lighting
void lightInit() {
	//generate a seperate VAO for lighting elements
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO); // bind this new VAO
	glGenBuffers(1, &lightVBO);
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
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.09f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	//stop the mouse looping round the z axis, can only go as high as the sky and the floor
	if (pitch < -89.0f)
		pitch = -89.0;
	if (pitch > 89.0f)
		pitch = 89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	cameraFront = glm::normalize(front);
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
		cameraPos -= cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
///_________________________________________________________________________________________________End of function

std::vector<int> faceSplitter(string word) {
	stringstream sWord(word);
	std::vector < int > values;
	string token;

	while (getline(sWord, token, '/')) {
		values.push_back(stoi(token));
	}

	vectorIndex.push_back(values.at(0));
	textureIndex.push_back(values.at(1));
	normalIndex.push_back(values.at(2));
	return values;
}

///Load OBJ
const char* filename = ".\\Creeper-obj\\Creeper.obj";
bool loadOBJ() {
	glm::vec3 tempVertice;
	glm::vec2 tempTexCoord;
	glm::vec3 tempNormal;

	cout << "Loading creeper.obj" << endl;

	string line;
	ifstream fileRead(filename);
	string header;

	if (fileRead.is_open()) {
		while (getline(fileRead, line)) {
			//cout << line << endl;
			stringstream linestream(line);
			string lineHead;
			linestream >> lineHead;

			if (lineHead == "v") {
				linestream >> tempVertice.x >> tempVertice.y >> tempVertice.z;
				vertices.push_back(tempVertice);
				//cout << tempVertice.x << tempVertice.y << tempVertice.z << endl;

			}
			else if (lineHead == "vt") {
				linestream >> tempTexCoord.x >> tempTexCoord.y;
				textureCoords.push_back(tempTexCoord);
				//cout << tempTexCoord.x << tempTexCoord.y << endl;

			}
			else if (lineHead == "vn") {
				linestream >> tempNormal.x >> tempNormal.y >> tempNormal.z;
				normals.push_back(tempNormal);
				//cout << tempNormal.x << tempNormal.y << tempNormal.z << endl;

			}
			else if (lineHead == "f") {
				char c;
				int numOfWords = 0;
				for (int i = 0; i < line.length(); i++) {
					c = line.at(i);
					if (isspace(c)) {
						numOfWords++;
					}
				}

				if (numOfWords == 4) {
					string w1, w2, w3, w4;
					linestream >> w1 >> w2 >> w3 >> w4;

					faceSplitter(w1);
					faceSplitter(w2);
					faceSplitter(w3);
					faceSplitter(w4);

					faceQuad.push_back(true);

					numOfFaces++;
				}

				if (numOfWords == 3) {
					string w1, w2, w3;
					linestream >> w1 >> w2 >> w3;

					faceSplitter(w1);
					faceSplitter(w2);
					faceSplitter(w3);

					faceQuad.push_back(false);

					numOfFaces++;
				}
			}
		}
		fileRead.close();
	}
	return true;
}
///_________________________________________________________________________________________________End of Function

///build the object
void objectBuilder() {


	int verticeReadIndex = 0;
	for (int i = 0; i < numOfFaces; i++) {
		if (faceQuad.at(i) == true) {

			for (int j = 0; j < 4; j++) {
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).x);
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).y);
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).z);

				object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).x);
				object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).y);
				object.push_back(vertices.at(normalIndex.at(verticeReadIndex) - 1).z);

				object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).x);
				object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).y);

				verticeReadIndex++;
			}

			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 0);
		}

		else if (faceQuad.at(i) == false) {
			for (int j = 0; j < 3; j++) {
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).x);
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).y);
				object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).z);

				object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).x);
				object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).y);
				object.push_back(vertices.at(normalIndex.at(verticeReadIndex) - 1).z);

				object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).x);
				object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).y);

				verticeReadIndex++;
			}

			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
		}
	}
}
///_________________________________________________________________________________________________End of Function



///main program run
int main() {
	cout << "Program Running..." << endl;
	cout << "Press escape to close software..." << endl << endl;
	loadOBJ();
	objectBuilder();

	//intialise the required GLFW things
	glewExperimental = GL_TRUE; //needed for some reason unknown
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window and check to see if the window opened correctly, if not terminate glfw and return error data
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Model_Loader", NULL, NULL);
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
	//create the shaders needed using the shader header to create the vertex and the fragment shader
	Shader basicShaders("mainVertex.vs", "mainFragment.fs");
	Shader lightShaders("lightVertex.vs", "lightFragment.fs");

	//further Inits
	triangleInit();
	shadersInit();
	textureInit();
	lightInit();


	glEnable(GL_DEPTH_TEST);

	basicShaders.run(); // don't forget to activate the shader before setting uniforms!  
	glUniform1i(glGetUniformLocation(basicShaders.ID, "texture1"), 0); // set it manually
	basicShaders.setInt("texture2", 1); // or with shader class
	basicShaders.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	basicShaders.setFloat("ambientLight", 0.3f);

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
		glBindTexture(GL_TEXTURE_2D, textureWall);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureFace);

		//draw the triangle using the shaders we have initialised
		basicShaders.run();

		glm::mat4 translation = glm::mat4(1.0f); // must initialize first or it would be null
		//translation = glm::rotate(translation, (float)glfwGetTime() / 4, glm::vec3(1.0, 0.0, 1.0));
		float scaleAmount = 0.7f;//sin(glfwGetTime());
		translation = glm::scale(translation, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		//glm::mat4 orthoMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		//projection matrix will give us perspective ( FOV				 ,	viewport w and h for aspect,  NPlane, far plane)		
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 300.0f);

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//viewMatrix = glm::translate(viewMatrix, cameraPos);

		//tranformations
		basicShaders.setMat4("transform", translation);
		basicShaders.setMat4("projection", projectionMatrix);
		basicShaders.setMat4("view", viewMatrix);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//repeate for 10 cubes
		for (int i = 0; i < 1; i++) {
			//model matrix
			glm::mat4 modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, objectPositions[i]);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
			basicShaders.setMat4("model", modelMatrix);

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}
		
		lightShaders.run();
		lightShaders.setMat4("transform", translation);
		lightShaders.setMat4("projection", projectionMatrix);
		lightShaders.setMat4("view", viewMatrix);
		
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::scale(translation, glm::vec3(0.4f, 0.4f, 0.4f));
		modelMatrix = glm::translate(modelMatrix, lightPosition);
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