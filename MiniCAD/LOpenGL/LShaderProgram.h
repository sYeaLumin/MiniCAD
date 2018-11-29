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

	LShaderProgram(QString vs, QString fs, LCamera & c) : 
		vsPath(vs), fsPath(fs), camera(c)
	{
	}
	~LShaderProgram(){}

	void init() {
		initializeOpenGLFunctions();
		addShaderFromSourceFile(QOpenGLShader::Vertex, vsPath);
		addShaderFromSourceFile(QOpenGLShader::Fragment, fsPath);
		if (link()) {
			qDebug() << "			LShaderProgram : Link !";
		}
		else {
			qDebug() << "			LShaderProgram : Link Failed !";
		}
	}
	virtual void setUniform() = 0;

protected:
	LCamera & camera;

private:
	QString vsPath;
	QString fsPath;
};

