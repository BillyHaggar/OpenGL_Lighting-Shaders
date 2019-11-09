/////image stb_image.h loader
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
/////openGL Libraries
//#include "GL/glew.h"
//#include "GL/freeglut.h"
//#include "GLFW/glfw3.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
/////own header files
//#include "Shader.h"
/////c++ libraries
//#include <iostream>
//
//using namespace std;
//
///*--------------------- SETTINGS AND GLOBAL VARIABLES ---------------------------------------------------------------------*/
/////Settings____________________________________________________
////set the window height and width here
//const unsigned int windowWidth = 1600; // default value 1600 width
//const unsigned int windowHeight = 1200; // default value 1200 width
//
//
//float lastX = windowWidth / 2;
//float lastY = windowHeight / 2;
//
//
/////GPU buffer__________________________________________________
//unsigned int VBO, VAO, EBO;
//
/////Triangles that make a cube__________________________________________________
////vertices are the points we will use with their colour and texture coordinates
//float cube[] = {
//	//points			  Colours			   Textures
//	 0.5f,  0.5f, -0.5f,  0.3f, 0.0f, 0.0f,    1.0f,  1.0f, // 0 near top right
//	 0.5f, -0.5f, -0.5f,  0.0f, 0.3f, 0.0f,    1.0f,  0.0f, // 1 near bottom right
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.3f,    0.0f,  0.0f, // 2 near bottom left
//	-0.5f,  0.5f, -0.5f,  0.3f, 0.3f, 0.0f,    0.0f,  1.0f, // 3 near top left 
//
//	 0.5f,  0.5f,  0.5f,  0.3f, 0.0f, 0.0f,    1.0f,  1.0f, // 4 far top right
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.3f, 0.0f,    1.0f,  0.0f, // 5 far bottom right
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.3f,    0.0f,  0.0f, // 6 far bottom left
//	-0.5f,  0.5f,  0.5f,  0.3f, 0.3f, 0.0f,    0.0f,  1.0f, // 7 far top left 
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.3f,    1.0f,  0.0f, // 8 left bottom right
//	-0.5f,  0.5f, -0.5f,  0.3f, 0.3f, 0.0f,    1.0f,  1.0f, // 9 left top right 
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.3f,    0.0f,  0.0f, // 10 left bottom left
//	-0.5f,  0.5f,  0.5f,  0.3f, 0.3f, 0.0f,    0.0f,  1.0f, // 11 left top left 
//
//	 0.5f,  0.5f,  0.5f,  0.3f, 0.0f, 0.0f,    1.0f,  1.0f, // 12 right top right
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.3f, 0.0f,    1.0f,  0.0f, // 13 right bottom right
//	 0.5f,  0.5f, -0.5f,  0.3f, 0.0f, 0.0f,    0.0f,  1.0f, // 14 right top left
//	 0.5f, -0.5f, -0.5f,  0.0f, 0.3f, 0.0f,    0.0f,  0.0f, // 15 right bottom left
//
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.3f, 0.0f,    1.0f,  1.0f, // 16 bottom top right?
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.3f,    0.0f,  1.0f, // 17 bottom top left?
//	 0.5f, -0.5f, -0.5f,  0.0f, 0.3f, 0.0f,    1.0f,  0.0f, // 18 bottom bottom right?
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.3f,    0.0f,  0.0f, // 19 bottom bottom left?
//
//	-0.5f,  0.5f, -0.5f,  0.3f, 0.3f, 0.0f,    0.0f,  0.0f, // 20 top bottom left?
//	 0.5f,  0.5f, -0.5f,  0.3f, 0.0f, 0.0f,    1.0f,  0.0f, // 21 top bottom right?
//	 0.5f,  0.5f,  0.5f,  0.3f, 0.0f, 0.0f,    1.0f,  1.0f, // 22 top top right?
//	-0.5f,  0.5f,  0.5f,  0.3f, 0.3f, 0.0f,    0.0f,  1.0f, // 23 top top left?
//};
////indices are the links between these points that will link up to make the triangles
//unsigned int indices[] = {  // note that we start from 0!
//	//front face
//	0, 1, 3,   // first triangle
//	1, 2, 3,    // second triangle
//	//back face
//	4, 5, 7,
//	5, 6, 7,
//	//left face
//	9, 8, 11,
//	8, 10, 11,
//	//right face
//	12, 13, 14,
//	13, 15, 14,
//	//bottom face
//	16, 18, 17,
//	18, 19, 17,
//	//top face
//	22, 21, 23,
//	21, 20, 23,
//};
/////cube origin posistions
//glm::vec3 cubePositions[10] = {
//  glm::vec3(0.0f,  0.0f,  0.0f),
//  glm::vec3(2.0f,  5.0f, -15.0f),
//  glm::vec3(-1.5f, -2.2f, -2.5f),
//  glm::vec3(-3.8f, -2.0f, -12.3f),
//  glm::vec3(2.4f, -0.4f, -3.5f),
//  glm::vec3(-1.7f,  3.0f, -7.5f),
//  glm::vec3(1.3f, -2.0f, -2.5f),
//  glm::vec3(1.5f,  2.0f, -2.5f),
//  glm::vec3(1.5f,  0.2f, -1.5f),
//  glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//
/////Textures______________________________________________________
//unsigned int textureWall;
//unsigned int textureFace;
////texture parameters
//int textureWidth, textureHeight, nrChannels;
////texture data stream when for when reading a image file with stb_library
//unsigned char *textureData;
///*---------------------------------------------------------------------------------------------------------------------------*/
//
/////transformation vector and matrix
////create a vector {x = 1, y = 0, z = 0, w = 1}
//glm::vec4 vector(1.0f, 0.0f, 0.0f, 1.0);
////create a translation matrix
//unsigned int transformLoc; // for when transforming a vector to give it a way to store the new location
/////Vclip = Mprojection * Mview * Mmodel * Mlocal variables to pass to vertex shader
//unsigned int projectionLoc;
//unsigned int viewLoc;
//unsigned int modelLoc;
//
/////Camera variables to be used by the view matrix
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//
//float deltaTime = 0.0f;	// Time between current frame and last frame
//float lastFrame = 0.0f; // Time of last frame
//
//bool firstMouse = true;
//float yaw = -90.0f;
//float pitch = 0.0f;
//float fov = 45.0f;
//
///*-------------------- FUNCTIONS -------------------------------------------------------------------------------------------*/
/////initialize the shaders and what they will be processing from the verticies and indicies
//void shadersInit() {
//	//vertex coordinates
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	//Colour
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	//texture coord attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//}
/////_________________________________________________________________________________________________End of function
//
/////initialize the triangle required functions, CREATE THE BUFFERS NEEDED FOR RENDERING
//void triangleInit() {
//	// generate the vertex array object
//	glGenVertexArrays(1, &VAO);
//	//generate the buffers
//	glGenBuffers(1, &VBO);
//	// generate the EBO for sharing points
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//bind the vertex array
//	glBindVertexArray(VAO);
//	//Bind the buffers
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//call the buffers and assign the triangles points to the buff-
//	//-er, what we are binding, size in data we want to allocate, the data to send to buff-
//	//-er how we want the GPU to manage (how often the data will change))
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
//}
/////_________________________________________________________________________________________________End of function
//
/////texture handler
////deal with generating and creating textures ready for the shaders to use
//void textureInit() {
//	// set the texture wrapping parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	// set texture filtering parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	///first texture
//	textureData = stbi_load("wall.jpg", &textureWidth, &textureHeight, &nrChannels, 0); //use stb_image to read the data from the texture file
//	//first argument is how many textures we want to bind, second is the reference to where we want to store them
//	glGenTextures(1, &textureWall);
//	//as before we now bind the textures we need
//	glBindTexture(GL_TEXTURE_2D, textureWall);
//	//now get the data and load it into the created texture space
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
//	//generate a mipmap(different size images to use) from the texture
//	glGenerateMipmap(GL_TEXTURE_2D);
//	stbi_image_free(textureData); // clear up the data now we dont need it
//
//	///second texture
//	stbi_set_flip_vertically_on_load(true);
//	//read the data from file
//	textureData = stbi_load("awesomeface.png", &textureWidth, &textureHeight, &nrChannels, 0);
//	glGenTextures(1, &textureFace);
//	glBindTexture(GL_TEXTURE_2D, textureFace);
//	//create the texture image
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
//	//same for the generation of mipMaps
//	glGenerateMipmap(GL_TEXTURE_2D);
//	stbi_image_free(textureData); // clear up the data now we dont need it
//
//}
/////_________________________________________________________________________________________________End of function
//
///////basic transofrmations function
//////deal with glm transformations
////void transformationFunction() {
////	translation = glm::rotate(translation, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
////	translation = glm::scale(translation, glm::vec3(0.5, 0.5, 0.5));
////
////	vector = translation * vector;
////	cout << "Matrix transformation coreect if 211 == " << vector.x << vector.y << vector.z << endl;
////}
///////_________________________________________________________________________________________________End of function
////
///////basic transofrmations function
//////deal with glm transformations
////void rotate() {
////	translation = glm::rotate(translation, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
////	translation = glm::scale(translation, glm::vec3(0.5, 0.5, 0.5));
////
////}
///////_________________________________________________________________________________________________End of function
//
/////viewport handler
////deal with window resizes and edit the render space
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//	lastX = width / 2;
//	lastY = height / 2;
//}
/////_________________________________________________________________________________________________End of function
//
/////Mouse callback hander function
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//		firstMouse = false;
//	}
//
//	float xOffset = xpos - lastX;
//	float yOffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.09f;
//	xOffset *= sensitivity;
//	yOffset *= sensitivity;
//
//	yaw += xOffset;
//	pitch += yOffset;
//
//	if (pitch < -89.0f)
//		pitch = -89.0;
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//
//	glm::vec3 front;
//	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
//	front.y = sin(glm::radians(pitch));
//	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//
//	cameraFront = glm::normalize(front);
//}
/////_________________________________________________________________________________________________End of function
//
/////Input handler
//// Basic function to check for inputs
//void processInput(GLFWwindow *window) {
//
//	float cameraSpeed = 4.5f * deltaTime;
//	//check for the escape key and check if its been pressed
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true); // if true close window
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraUp;
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraUp;
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront;;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//}
/////_________________________________________________________________________________________________End of function
//
/////main program run
//int main() {
//	cout << "Program Running..." << endl;
//	cout << "Press escape to close software..." << endl << endl;
//	//intialise the required GLFW things
//	glewExperimental = GL_TRUE; //needed for some reason unknown
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//	//create the window and check to see if the window opened correctly, if not terminate glfw and return error data
//	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window); //target window of open gl we created
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // create call back to for window resize
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouse_callback);
//
//	glewInit(); // initialise glew componenets
//	//create the shaders needed using the shader header to create the vertex and the fragment shader
//	Shader basicShaders("vertexShader.vs", "fragmentShader.fs");
//	//further Inits
//	triangleInit();
//	//initialise the shaders
//	shadersInit();
//	//now apply the textures
//	textureInit();
//
//	glEnable(GL_DEPTH_TEST);
//
//	//draw in wireframe mode
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//draw in regular mode
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//
//	basicShaders.run(); // don't forget to activate the shader before setting uniforms!  
//	glUniform1i(glGetUniformLocation(basicShaders.ID, "texture1"), 0); // set it manually
//	basicShaders.setInt("texture2", 1); // or with shader class
//
//
//
//
//	//Main drawing loop, effectivly what will happen evey frame (easy way to think about it)
//	while (!glfwWindowShouldClose(window)) {
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);// the key checks above for the escape key to close the window (own version)
//		// rendering commands here
//		glClearColor(0.15f, 0.1f, 0.15f, 0.5f); //set background render colour
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the colour buffer
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, textureWall);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, textureFace);
//
//		//draw the triangle using the shaders we have initialised
//		basicShaders.run();
//
//
//		glm::mat4 translation = glm::mat4(1.0f); // must initialize first or it would be null
//		translation = glm::rotate(translation, (float)glfwGetTime() / 4, glm::vec3(1.0, 0.0, 1.0));
//		float scaleAmount = 0.8f;//sin(glfwGetTime());
//		translation = glm::scale(translation, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
//		//glm::mat4 orthoMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
//		//projection matrix will give us perspective ( FOV				 ,	viewport w and h for aspect,  NPlane, far plane)		
//		glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
//
//		glm::mat4 viewMatrix = glm::mat4(1.0f);
//		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//		//viewMatrix = glm::translate(viewMatrix, cameraPos);
//
//
//		//tranformations
//		transformLoc = glGetUniformLocation(basicShaders.ID, "transform");
//		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translation));
//		viewLoc = glGetUniformLocation(basicShaders.ID, "view");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//		projectionLoc = glGetUniformLocation(basicShaders.ID, "projection");
//		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//
//		glBindVertexArray(VAO);
//
//		//repeate for 10 cubes
//		for (int i = 0; i < 10; i++) {
//			//model matrix
//			glm::mat4 modelMatrix = glm::mat4(1.0f);
//			modelMatrix = glm::rotate(modelMatrix, glm::radians(20.0f), glm::vec3(1.0, 0.0, 0.0));
//			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
//			modelLoc = glGetUniformLocation(basicShaders.ID, "model");
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//
//			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
//		}
//
//		glfwSwapBuffers(window); //another buffer for rendering
//		glfwPollEvents(); // Deals with pollling events such as key events
//	}
//
//	//de-allocate all resources once they've outlived their purpose:
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	//clean up and close down correctly
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;//return 0, exited normally
//}
/////_________________________________________________________________________________________________End of function