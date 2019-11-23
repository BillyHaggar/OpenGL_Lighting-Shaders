#include "Loader.h"
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

	using namespace std;
	Loader::Loader(){

	}
	///split each element of a face
	bool Loader::faceSplitter(string word) {
		stringstream sWord(word);
		std::vector<int> values;
		string token;

		while (getline(sWord, token, '/')) {
			values.push_back(stoi(token));
		}

		vectorIndex.push_back(values.at(0));
		textureIndex.push_back(values.at(1));
		normalIndex.push_back(values.at(2));
		return true;
	}
	///_________________________________________________________________________________________________End of Function

	///Load OBJ
	bool Loader::loadOBJ(const char * filePath) {
		cout << "Loading: " << filePath << endl;

		string line;
		ifstream fileRead(filePath);
		string header;
		string mtl;

		if (fileRead.is_open()) {
			while (getline(fileRead, line)) {
				//cout << line << endl;
				stringstream linestream(line);
				string lineHead;
				linestream >> lineHead;

				if (lineHead == "mtllib") {
					linestream >> materialFile;
				} 
				else if (lineHead == "v") {
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
				else if (lineHead == "usemtl") {
					linestream >> mtl;
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
						faceMtl.push_back(mtl);

						numOfFaces++;
					}

					if (numOfWords == 3) {
						string w1, w2, w3;
						linestream >> w1 >> w2 >> w3;

						faceSplitter(w1);
						faceSplitter(w2);
						faceSplitter(w3);

						faceQuad.push_back(false);
						faceMtl.push_back(mtl);

						numOfFaces++;
					}
				}
			}
			fileRead.close();
		}
		cout << "Loading Complete" << endl;
		return true;
	}
	///_________________________________________________________________________________________________End of Function

	///build the object
	void Loader::objectBuilder(std::vector <float> &object, std::vector <int> &indices, std::vector<Material> materials) {
		cout << "Building object..." << endl;
		
		bool noMatch = true;
		//add colour(kd) to it
		for (int i = 0; i < numOfFaces; i++) {
			noMatch = true;
			for (int j = 0; j < materials.size(); j++) {
				if (materials.at(j).materialName == faceMtl.at(i)) {
					//cout << materials.at(j).Kd.x << ", " << materials.at(j).Kd.y << ", " << materials.at(j).Kd.z << endl;
					colors.push_back(materials.at(j).Kd);
					noMatch = false;
				}
			} 
			if (noMatch == true) {
				colors.push_back(materials.at(0).Kd);
			}
		
		}
		

		int verticeReadIndex = 0;
		for (int i = 0; i < numOfFaces; i++) {
			if (faceQuad.at(i) == true) {

				for (int j = 0; j < 4; j++) {
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).x);
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).y);
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).z);

					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).x);
					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).y);
					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).z);

					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).x);
					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).y);

					object.push_back(colors.at(i).x);
					object.push_back(colors.at(i).y);
					object.push_back(colors.at(i).z);
					
					verticeReadIndex++;
				}

				indices.push_back(verticeReadIndex - 4);
				indices.push_back(verticeReadIndex - 3);
				indices.push_back(verticeReadIndex - 2);
				indices.push_back(verticeReadIndex - 2);
				indices.push_back(verticeReadIndex - 1);
				indices.push_back(verticeReadIndex - 4);
			}

			else if (faceQuad.at(i) == false) {
				for (int j = 0; j < 3; j++) {
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).x);
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).y);
					object.push_back(vertices.at(vectorIndex.at(verticeReadIndex) - 1).z);

					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).x);
					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).y);
					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).z);

					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).x);
					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).y);

					object.push_back(colors.at(i).x);
					object.push_back(colors.at(i).y);
					object.push_back(colors.at(i).z);

					verticeReadIndex++;
				}
				indices.push_back(verticeReadIndex - 3);
				indices.push_back(verticeReadIndex - 2);
				indices.push_back(verticeReadIndex - 1);

			}
		}
		cout << "Building Complete" << endl << endl;
	}
	///_________________________________________________________________________________________________End of Function

	///Load mtlfile
	bool Loader::loadMTL(const char* filePath, std::vector<Material> &vector) {

		Material mat;
		cout << "Loading: " << filePath << endl;

		string line;
		ifstream fileRead(filePath);
		string header;
		bool firstMtl = true;

		if (fileRead.is_open()) {
			while (getline(fileRead, line)) {
				stringstream linestream(line);
				string lineHead;
				linestream >> lineHead;
				if (lineHead == "newmtl" && firstMtl == true) {
					linestream >> mat.materialName;
					firstMtl = false;
				}
				else if (lineHead == "Ns") {
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
					if (mat.map_Kd != "") {
						Loader::hasTexture = true;
					}
				}
				else if (lineHead == "map_d") {
					linestream >> mat.map_d;

				}else if (lineHead == "newmtl" && firstMtl == false) {
					vector.push_back(mat);
					linestream >> mat.materialName;
				}
				
			}
			fileRead.close();

			vector.push_back(mat);
		}
		cout << "Loading Complete" << endl;
		return true;
	}
	///_________________________________________________________________________________________________End of Function
#ifdef __cplusplus
};
#endif // __cplusplus
