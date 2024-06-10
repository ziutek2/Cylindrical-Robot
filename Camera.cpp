#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 center)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	Camera::center = center;
	
	
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(0.1f);
	glm::mat4 projection = glm::mat4(1.0f);


	// Makes camera look in the right direction from the right position

	view = glm::lookAt(Position, center, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& Shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(Shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}



void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		
		Position += speed * -Orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		
		Position = glm::rotate(Position,-glm::radians(speed* angle), Up);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

			Position = glm::rotate(Position, glm::radians(speed * angle), Up);
	} 
		// Handles mouse inputs
		
	}
