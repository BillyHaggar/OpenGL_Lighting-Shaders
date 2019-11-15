///shader.h creates both a vertex shader and a fragment shader by passing in GLSL txt files
//define what this file is
#ifndef Shader_h
#define Shader_h

//includes for open gl
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
//c++ includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//just tidies up the repeated use of std::
using namespace std;

/// shader, deals with creating both a vertex shader and a fragment shader in this one file
class Shader
{
public:
	unsigned int ID;

	// constructor reads and builds a fragemnt shader and a vertex shader and attaches them to the program it called from
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		string vertexShaderText;
		string fragmentShaderText;
		ifstream vShaderFile;
		ifstream fShaderFile;
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;
			// read the shader files and put into a stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// convert stream into string
			vertexShaderText = vShaderStream.str();
			fragmentShaderText = fShaderStream.str();
			// close the steams for both shaders
			vShaderFile.close();
			fShaderFile.close();
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR - Problem reading from the vs and fs files, check these maybe?" << endl;
		}


		//compile and bind shaders to the program
		const char* vShaderCode = vertexShaderText.c_str();
		const char * fShaderCode = fragmentShaderText.c_str();
		unsigned int vertex, fragment;

		// vertex shader creation
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// fragment Shader creation
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		// create the shader Program
		ID = glCreateProgram();
		//attach the shader to the program and link to the program they are called to
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// use/activate the shader
	void run() {
		glUseProgram(ID);
	}
	//set the ID from main with this ()basic getter and setter
	void setInt(const string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	void setFloat(const string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};
#endif // Shader_h