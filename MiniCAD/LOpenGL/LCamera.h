#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\euler_angles.hpp>
#define PI 3.1415926

class LCamera
{
private:
	float Width, Height;
	float Fovy;
	float pitch, yaw, radius;
	glm::vec3 cEye, cCenter, cUp;
	glm::vec3 front, right;
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat, projMat;

	float lastx, lasty;
	float speed = 0.01;

public:

	LCamera() {}
	~LCamera(){}

	void init(float w, float h,
		glm::vec3 eye = glm::vec3(2.0f, 3.0f, 5.0f),
		glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f),
		float fovy = glm::radians(60.0f))
	{
		Width = w;
		Height = h;
		Fovy = fovy;
		cEye = eye;
		cCenter = center;
		radius = glm::length(eye - center);
		glm::vec3 dir = glm::normalize(eye - center);
		yaw = glm::atan(dir.x, dir.z);
		pitch = glm::asin(dir.y);
		upDate2();
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

	void upDate2() {
		glm::vec3 dir;
		dir.y = glm::sin(pitch);
		dir.x = glm::cos(pitch)*glm::sin(yaw);
		dir.z = glm::cos(pitch)*glm::cos(yaw);
		cEye = cCenter + dir*radius;
		front = glm::normalize(cCenter - cEye);
		right = glm::normalize(glm::cross(front, worldUp));
		cUp = glm::normalize(glm::cross(right, front));
		viewMat = glm::lookAt(cEye, cCenter, cUp);
		projMat = glm::perspective(Fovy, Width / Height, 0.1f, 1000.0f);
	}

	void click(float x, float y) {
		lastx = x;
		lasty = y;
	}

	void orientate(float x, float y) {
		float xoffset = x - lastx;
		float yoffset = y - lasty;
		lastx = x;
		lasty = y;
		pitch += speed * yoffset;
		yaw -= speed * xoffset;
		if (pitch > PI / 2)
			pitch = PI / 2;
		if (pitch < -PI / 2)
			pitch = -PI / 2;
		upDate2();
	}

	void move(float x, float y) {
		float xoffset = x - lastx;
		float yoffset = y - lasty;
		lastx = x;
		lasty = y;
		cCenter -= right * speed * xoffset;
		cCenter += cUp * speed * yoffset;
		cEye -= right * speed * xoffset;
		cEye += cUp * speed * yoffset;
		radius = glm::length(cEye - cCenter);
		upDate2();
	}

	void zoom(float delta) {
		delta /= abs(delta);
		radius -= delta * speed * 5;
		upDate2();
	}

	void Log() {
		qDebug() << "Camera : ";
		qDebug() << "cCenter : " << cCenter.x << " " << cCenter.y << " " << cCenter.z;
		qDebug() << "cEye : " << cEye.x << " " << cEye.y << " " << cEye.z;
		qDebug() << "pitch : " << pitch;
		qDebug() << "yaw : " << yaw;
	}
};

