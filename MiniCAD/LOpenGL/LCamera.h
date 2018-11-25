#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\euler_angles.hpp>
class LCamera
{
private:
	float Width, Height;
	float Fovy;
	glm::vec3 cEye, cCenter, cUp;
	glm::vec3 front, right;
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat, projMat;

public:

	LCamera() {}
	~LCamera(){}

	void init(float w, float h,
		glm::vec3 eye = glm::vec3(2.0f, 5.0f, 5.0f),
		glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f),
		float fovy = glm::radians(60.0f))
	{
		Width = w;
		Height = h;
		Fovy = fovy;
		cEye = eye;
		cCenter = center;
		upDate();
	}

	float getWidth() { return Width; }
	float getHeight() { return Height; } 
	glm::vec3  getEye() { return cEye; }
	glm::mat4 getViewMat() { return viewMat; }
	glm::mat4 getProjMat() { return projMat; }

	float setWidth(float w) { return Width = w; }
	float setHeight(float h) { return Height = h; }
	glm::vec3 setEye(glm::vec3 e) { return cEye = e; }
	glm::vec3 setCenter(glm::vec3 c) { return cCenter = c; }

	void upDate() {
		front = glm::normalize(cCenter - cEye);
		right = glm::normalize(glm::cross(front, worldUp));
		cUp = glm::normalize(glm::cross(right, front));
		viewMat = glm::lookAt(cEye, cCenter, cUp);
		projMat = glm::perspective(Fovy, Width / Height, 0.1f, 1000.0f);
	}
};

