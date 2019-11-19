#include "Camera.h"

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

Camera::Camera()
{
	init();
}

void init() {
	std::cout << "hello from camera" << std::endl;

}

#ifdef __cplusplus
};
#endif // __cplusplus




