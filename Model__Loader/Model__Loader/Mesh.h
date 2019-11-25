#ifndef Mesh_h
#define Mesh_h

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

using namespace std;

class Mesh
{
public:
	Mesh(std::vector<float> object, std::vector<int> indices, bool hasTexture);
	void setupMesh();
	void setupTexture();
	void swapTexture();
	unsigned int VBO, VAO, EBO;
	std::vector<float> object;
	std::vector<int> indices;
	bool hasTexture;

	///Textures______________________________________________________
	unsigned int texture;
	int textureWidth, textureHeight, nrChannels;
	unsigned char * textureData;


};

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // Mesh Header

