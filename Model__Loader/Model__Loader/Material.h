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

	///Load mtlfile
	//bool loadMTL(const char* filePath) {

	//	cout << "Loading" << filePath << endl;

	//	string line;
	//	ifstream fileRead(filePath);
	//	string header;

	//	if (fileRead.is_open()) {
	//		while (getline(fileRead, line)) {
	//			stringstream linestream(line);
	//			string lineHead;
	//			linestream >> lineHead;

	//			if (lineHead == "Ns") {
	//				linestream >> Ns;

	//			}
	//			else if (lineHead == "Ka") {
	//				linestream >> Ka.x >> Ka.y >> Ka.z;

	//			}
	//			else if (lineHead == "Kd") {
	//				linestream >> Kd.x >> Kd.y >> Kd.z;

	//			}
	//			else if (lineHead == "Ks") {
	//				linestream >> Ks.x >> Ks.y >> Ks.z;

	//			}
	//			else if (lineHead == "Ke") {
	//				linestream >> Ke.x >> Ke.y >> Ke.z;

	//			}
	//			else if (lineHead == "Ni") {
	//				linestream >> Ni;

	//			}
	//			else if (lineHead == "d") {
	//				linestream >> d;

	//			}
	//			else if (lineHead == "illum") {
	//				linestream >> illum;

	//			}
	//			else if (lineHead == "map_Kd") {
	//				linestream >> map_Kd;

	//			}
	//			else if (lineHead == "map_d") {
	//				linestream >> map_d;

	//			}
	//		}
	//		fileRead.close();
	//	}
	//	return true;
	//}
	///_________________________________________________________________________________________________End of Function
};

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // Material Header
