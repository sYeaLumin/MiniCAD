#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <qdebug.h>
#include "LOpenGL\LCamera.h"
#include "LineShaderProgram.h"
#include "FaceShaderProgram.h"
#include "Modeler.h"

const static char* const FaceVSPath = "./LOpenGL/Lights.vert";
const static char* const FaceFSPath = "./LOpenGL/Lights.frag";
const static char* const LineVSPath = "./LOpenGL/Base.vert";
const static char* const LineFSPath = "./LOpenGL/Base.frag";

enum MouseActionType {
	Press,
	Move,
	Release
};

class MiniCADWidget :
	public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	MiniCADWidget(QWidget *parent = nullptr);//QWidget *parent£¿
	~MiniCADWidget();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void mousePressEvent(QMouseEvent *mouseEvent) override;
	void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QMouseEvent *mouseEvent) override;
	void wheelEvent(QWheelEvent *wheelEvent) override;

private:
	void cameraOperate(QMouseEvent * mouseEvent, MouseActionType type);

private:
	LCamera camera;
	LineShaderProgram Lineshader;
	FaceShaderProgram Faceshader;
	Modeler modeler;
};

