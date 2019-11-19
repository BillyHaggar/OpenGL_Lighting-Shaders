#ifndef Camera_h
#define Camera_h

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

class Camera
{
public:
	Camera();
	
	//initial stating location of the camera
	glm::vec3 cameraPos = glm::vec3(1.0, 1.0, 5.0);;
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

	//initial variables of the x,y,z coodinates of the camera pointing direction
	//remember that this is acheived by actually mving everything to give the illusion of camera movement
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	//mouse variables, used to know where the camer is pointing, initail variables set the starting location
	bool firstMouse = true;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float fov = 60.0f; //starting FOV, can be used to give the illusion of zooming in by decreasing (45.0f is a good basis to start)

private:
	
};

void init();


#ifdef __cplusplus
};
#endif // __cplusplus

#endif // Camera Header


