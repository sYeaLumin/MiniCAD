#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	camera(geometry().width(), geometry().height()),
	shader(LightVSPath, LightFSPath, camera)
{
	//≤‚ ‘cube
	qDebug() << "Window W&H : " << this->frameGeometry().width() << " " << this->frameGeometry().height();
	modeler.testModelCube();
}


MiniCADWidget::~MiniCADWidget()
{
}

void MiniCADWidget::initializeGL()
{
	initializeOpenGLFunctions();
	modeler.init();
	shader.init();
	glViewport(0, 0, geometry().width(), geometry().height());//?
	glClearColor(0.8, 1.0, 1.0, 1.0);
}

void MiniCADWidget::paintGL()
{
	glClearColor(0.8, 1.0, 1.0, 1.0);
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
