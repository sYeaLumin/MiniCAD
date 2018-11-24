#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <qdebug.h>
#include "LOpenGL\LCamera.h"
#include "LOpenGL\LShaderProgram.h"
#include "Modeler.h"

const static char* const LightVSPath = "./LOpenGL/Base.vert";
const static char* const LightFSPath = "./LOpenGL/Base.frag";

class MiniCADWidget :
	public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	MiniCADWidget(QWidget *parent = nullptr);//QWidget *parent��
	~MiniCADWidget();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void mousePressEvent(QMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QMouseEvent *mouseEvent) override;

private:
	LCamera camera;
	LShaderProgram shader;
	Modeler modeler;
};

