#include "Loader.h"

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
		cout << "Loading" << filePath << endl;

		string line;
		ifstream fileRead(filePath);
		string header;

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
	void Loader::objectBuilder(std::vector <float> &object, std::vector <int> &indices) {


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
					object.push_back(normals.at(normalIndex.at(verticeReadIndex) - 1).z);

					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).x);
					object.push_back(textureCoords.at(textureIndex.at(verticeReadIndex) - 1).y);

					indices.push_back(i * 3 + 0);
					indices.push_back(i * 3 + 1);
					indices.push_back(i * 3 + 2);

					verticeReadIndex++;
				}


			}
		}
	}
	///_________________________________________________________________________________________________End of Function


#ifdef __cplusplus
};
#endif // __cplusplus
