#include "FrameBuffer.h"

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	using namespace std;
	
	FrameBuffer::FrameBuffer(Shader inShader){
		this->shader = inShader;

	}

#ifdef __cplusplus
};
#endif // __cplusplus