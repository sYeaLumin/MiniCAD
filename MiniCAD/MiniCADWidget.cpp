#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	camera(),
	shader(LightVSPath, LightFSPath, camera)
{
	modeler.testModelCube();
}


MiniCADWidget::~MiniCADWidget()
{
}

void MiniCADWidget::initializeGL()
{
	initializeOpenGLFunctions();
	camera.init(geometry().width(), geometry().height());
	modeler.init();
	shader.init();
	glViewport(0, 0, geometry().width(), geometry().height());//?
	glEnable(GL_MULTISAMPLE);
}

void MiniCADWidget::paintGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw
	modeler.drawLine(shader);
}

void MiniCADWidget::resizeGL(int width, int height)
{
}

void MiniCADWidget::mousePressEvent(QMouseEvent * mouseEvent)
{
}

void MiniCADWidget::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
}

void MiniCADWidget::mouseMoveEvent(QMouseEvent * mouseEvent)
{
}
