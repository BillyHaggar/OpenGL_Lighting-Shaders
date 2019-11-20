#include "Material.h"

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus



Material::Material()
{
}

///Load mtlfile
bool Material::loadMTL(const char* filePath, Material &mat) {

	cout << "Loading" << filePath << endl;

	string line;
	ifstream fileRead(filePath);
	string header;


	if (fileRead.is_open()) {
		while (getline(fileRead, line)) {
			stringstream linestream(line);
			string lineHead;
			linestream >> lineHead;

			if (lineHead == "Ns") {
				linestream >> mat.Ns;

			}
			else if (lineHead == "Ka") {
				linestream >> mat.Ka.x >> mat.Ka.y >> mat.Ka.z;

			}
			else if (lineHead == "Kd") {
				linestream >> mat.Kd.x >> mat.Kd.y >> mat.Kd.z;

			}
			else if (lineHead == "Ks") {
				linestream >> mat.Ks.x >> mat.Ks.y >> mat.Ks.z;

			}
			else if (lineHead == "Ke") {
				linestream >> mat.Ke.x >> mat.Ke.y >> mat.Ke.z;

			}
			else if (lineHead == "Ni") {
				linestream >> mat.Ni;

			}
			else if (lineHead == "d") {
				linestream >> mat.d;

			}
			else if (lineHead == "illum") {
				linestream >> mat.illum;

			}
			else if (lineHead == "map_Kd") {
				linestream >> mat.map_Kd;

			}
			else if (lineHead == "map_d") {
				linestream >> mat.map_d;

			}
		}
		fileRead.close();
	}
	return true;
}
///_________________________________________________________________________________________________End of Function

#ifdef __cplusplus
};
#endif // __cplusplus
