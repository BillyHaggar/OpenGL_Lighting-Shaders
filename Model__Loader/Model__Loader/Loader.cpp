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
#include <regex>


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

	///Load loadDAE
	void Loader::loadDAE(const char * filePath, std::vector <float> &object, std::vector <int> &indices) {
		cout << "Loading: " << filePath << endl;

		string line;
		ifstream fileRead(filePath);
		Material tempMaterial;
		std::vector<Material> materials;

		string vertexLine;
		string normalLine;
		string textureLine;
		string faceLine;
		string materialLine;
		string colorLine;
		glm::vec3 defaultTexCood(1.0f);
		glm::vec3 color(1.0f);
		int i = 0;

		regex floatPositionReg("\\s*<float_array.*positions.*");
		regex floatNormalReg("\\s*<float_array.*normals.*");
		regex floatTextureReg("\\s*<float_array.*map.*");
		regex floatFaceReg("\\s*<p>.*");
		regex materialNameReg("\\s*<\\s*effect.*>");
		regex materialEndReg("\\s*</\\s*effect\\s*>");
		string q = "\"";
		regex floatColorReg("\\s*<\\s*color.*sid=" + q + "diffuse" + q + ".*>");
		regex textureReg("\s*<init_from>.*\.png.*");
		regex endOfMeshReg("\\s*</\\s*mesh\\s*>");
		regex materialSetReg("\\s*<\\s*triangles\\s*.*");
		smatch m;
		bool read = false;

		if (fileRead.is_open()) {
			while (getline(fileRead, line)) {
				//if line contains the start of whats needed
				if (regex_search(line, m, floatPositionReg) == true) {
					vertexLine = line;
					vertexLine = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) -1);
					stringstream ss(vertexLine);
					float x, y, z;
					while (ss >> x >> y >> z) {
						tempVertice.x = x;
						tempVertice.y = y;
						tempVertice.z = z;
						vertices.push_back(tempVertice);
					}
					
				}
				else if (regex_search(line, m, floatNormalReg) == true) {
					normalLine = line;
					normalLine = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) - 1);
					stringstream ss(normalLine);
					float x, y, z;
					while (ss >> x >> y >> z) {
						tempNormal.x = x;
						tempNormal.y = y;
						tempNormal.z = z;
						normals.push_back(tempNormal);
					}
				}
				else if (regex_search(line, m, floatTextureReg) == true) {
					textureLine = line;
					textureLine = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) - 1);
					stringstream ss(textureLine);
					float x, y, z;
					while (ss >> x >> y) {
						tempTexCoord.x = x;
						tempTexCoord.y = y;
						textureCoords.push_back(tempTexCoord);
					}
				}
				else if (regex_search(line, m, floatFaceReg) == true) {
					faceLine = line;
					faceLine = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) - 1);
					stringstream ss(faceLine);
					int x, y, z;
					
					while (ss >> x >> y >> z) {
						object.push_back(vertices.at(x).x);
						object.push_back(vertices.at(x).y);
						object.push_back(vertices.at(x).z);

						object.push_back(normals.at(y).x);
						object.push_back(normals.at(y).y);
						object.push_back(normals.at(y).z);
						
						object.push_back(textureCoords.at(z).x);
						object.push_back(textureCoords.at(z).y);

						object.push_back(color.x);
						object.push_back(color.y);
						object.push_back(color.z);

						indices.push_back(i);
						i++;
					}
						
				}
				else if (regex_search(line, m, materialNameReg) == true) {
					materialLine = line;
					materialLine = line.substr((line.find("\"") + 1), line.find(">") - (line.find("\"")) - 9);
					tempMaterial.materialName = materialLine;
				}
				else if (regex_search(line, m, floatColorReg) == true) {
					colorLine = line;
					colorLine = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) - 1);
					stringstream ss(colorLine);
					ss >> color.x >> color.y >> color.z;
					tempMaterial.Kd = color;
				}
				else if (regex_search(line, m, materialEndReg) == true) {
					materials.push_back(tempMaterial);
				}
				else if (regex_search(line, m, textureReg) == true) {
					hasTexture = true;
					string textureAddress;
					textureAddress = line.substr((line.find(">") + 1), line.find("</") - (line.find(">")) - 1);;
					for (int j = 0; j < materials.size(); j++) {
						materials.at(j).map_Kd = textureAddress;
					}
				}
				else if (regex_search(line, m, endOfMeshReg) == true) {
					vertices.erase(vertices.begin(), vertices.end());
					textureCoords.erase(textureCoords.begin(), textureCoords.end());
					normals.erase(normals.begin(), normals.end());
				}
				else if (regex_search(line, m, materialSetReg) == true) {
					materialLine = line;
					materialLine = line.substr((line.find("\"") + 1), line.find("\" count") - (line.find("\"")) - 10);
					for (int j = 0; j < materials.size(); j++) {
						if (materials.at(j).materialName == materialLine) {
							color = materials.at(j).Kd;
						}
					}
				}
			}
			fileRead.close();
		}
		
	}
	///_________________________________________________________________________________________________End of Function

#ifdef __cplusplus
};
#endif // __cplusplus
