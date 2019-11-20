#ifndef Material_h
#define Material_h

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

	using namespace std;
class Material
{
public:
	Material();
	float Ns;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Ke;
	float Ni;
	float d;
	int illum;
	string map_Kd;
	string map_d;

	bool loadMTL(const char* filePath, Material &mat);
};

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // Material Header
