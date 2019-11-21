#ifndef Loader_h
#define Loader_h

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

#include <iostream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

	using namespace std;

	class Loader {
	public:
		Loader();
		bool loadOBJ(const char * filePath);
		bool loadMTL(const char* filePath, std::vector<Material> &vector);


		//temp loaded object data
		string materialFile;
		std::vector < glm::vec3 > vertices; //vector point for the object
		std::vector < glm::vec2 > textureCoords; // texture coordinates for the object
		std::vector < glm::vec3 > normals;	// normal coordinates for the object
		std::vector < int > vectorIndex, textureIndex, normalIndex; //each vertices element index ((element.at(index) - 1) == index to link to above)
		int numOfFaces = 0; //total number of faces for the object
		std::vector < bool > faceQuad; //for each face there needs to be a specification if that face is a quad or a tri so it can be converted accordingly

		glm::vec3 tempVertice;
		glm::vec2 tempTexCoord;
		glm::vec3 tempNormal;

		bool faceSplitter(string word);

		void objectBuilder(std::vector <float> &object, std::vector <int> &indices);

	};
	

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // Loader Header

