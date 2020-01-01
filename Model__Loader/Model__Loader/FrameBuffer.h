#ifndef FrameBuffer_h
#define FrameBuffer_h

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "Shader.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

	using namespace std;

	class FrameBuffer
	{
	public:
		FrameBuffer(Shader inShader);
		Shader shader;

	};

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // FrameBuffer Header

