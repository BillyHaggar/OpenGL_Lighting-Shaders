
#include "stb_image.h"

#include "Mesh.h"

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	using namespace std;

Mesh::Mesh(std::vector<float> object, std::vector<int> indices, bool hasTexture){
	this->object = object;
	this->indices = indices;
	this->hasTexture = hasTexture;
	setupMesh();
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//vertex coordinates offsets and locations
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal coordinates offsets and locations
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//texture coordinates offsets and locations
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//colour coordinates offsets and locations
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	//Bind data to the buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, object.size() * sizeof(float), &object[0], GL_STATIC_DRAW);


	///REALLY MESSY NEED TO FIX TEXTURES
	const char * texturePath;
	texturePath = "Media\\Image.png";
	if (hasTexture == true) {
		texturePath = "Media\\Objects\\Creeper-obj\\Texture.png";
	}

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	//read the data from file
	textureData = stbi_load(texturePath, &textureWidth, &textureHeight, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//create the texture image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	//same for the generation of mipMaps
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData); // clear up the data now we dont need it
}

#ifdef __cplusplus
};
#endif // __cplusplus
