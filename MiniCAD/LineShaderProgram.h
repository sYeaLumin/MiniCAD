#pragma once
#include "LOpenGL\LShaderProgram.h"
class LineShaderProgram :
	public LShaderProgram
{
public:

	LineShaderProgram(QString vs, QString fs, LCamera & c) :
		LShaderProgram(vs, fs, c){}

	~LineShaderProgram(){}

	void setUniform() override 
	{
		glUniformMatrix4fv(uniformLocation("modelMat"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glUniformMatrix4fv(uniformLocation("viewMat"), 1, GL_FALSE, glm::value_ptr(camera.getViewMat()));
		glUniformMatrix4fv(uniformLocation("projMat"), 1, GL_FALSE, glm::value_ptr(camera.getProjMat()));
		//glUniform3fv(uniformLocation("lightPos"), 1, glm::value_ptr(lightPos));
		//glUniform3fv(uniformLocation("viewPos"), 1, glm::value_ptr(camera.getEye()));
	}
};

