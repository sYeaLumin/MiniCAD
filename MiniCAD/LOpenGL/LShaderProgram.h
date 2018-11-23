#pragma once
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>
#include <gtc\type_ptr.hpp>
#include "LCamera.h"

class LShaderProgram :
	public QOpenGLShaderProgram, protected QOpenGLFunctions
{
public:

	LShaderProgram(QString vsPath, QString fsPath, LCamera & c) : 
		camera(c)
	{
		initializeOpenGLFunctions();
		addShaderFromSourceFile(QOpenGLShader::Vertex, vsPath);
		addShaderFromSourceFile(QOpenGLShader::Fragment, fsPath);
		link();
	}
	~LShaderProgram(){}

	void setUniform() {
		glUniformMatrix4fv(uniformLocation("modelMat"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniformMatrix4fv(uniformLocation("viewMat"), 1, GL_FALSE, glm::value_ptr(camera.getViewMat()));
		glUniformMatrix4fv(uniformLocation("projMat"), 1, GL_FALSE, glm::value_ptr(camera.getProjMat()));
		glUniform3fv(uniformLocation("lightPos"), 1, glm::value_ptr(lightPos));
		glUniform3fv(uniformLocation("viewPos"), 1, glm::value_ptr(camera.getEye()));
	}

protected:
	LCamera & camera;

private:
	glm::vec3 lightPos = glm::vec3(0.0f, 50.0f, 0.0f);
};

