#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	camera(),
	shader(LightVSPath, LightFSPath, camera)
{
	//modeler.testModelCube2();
	modeler.testModelCubeWithHole2();
	modeler.setupLineData3();
	//modeler.setupLineData2();
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
	makeCurrent();
	int x = mouseEvent->x();
	int y = mouseEvent->y();
	cameraOperate(mouseEvent, Press);
	update();
}

void MiniCADWidget::mouseReleaseEvent(QMouseEvent * mouseEvent)
{
	makeCurrent();
	cameraOperate(mouseEvent, Release);
	update();
}

void MiniCADWidget::mouseMoveEvent(QMouseEvent * mouseEvent)
{
	makeCurrent();
	int x = mouseEvent->x();
	int y = mouseEvent->y();
	cameraOperate(mouseEvent, Move);
	update();
}

void MiniCADWidget::wheelEvent(QWheelEvent * wheelEvent)
{
	makeCurrent();
	int delta = wheelEvent->delta();
	camera.zoom(delta);
	update();
}

void MiniCADWidget::cameraOperate(QMouseEvent * mouseEvent, MouseActionType type)
{
	int x = mouseEvent->x();
	int y = mouseEvent->y();
	switch (type) {
	case Press:
		camera.click(x, y);
		break;
	case Move:
		if (mouseEvent->buttons() & Qt::LeftButton)
			camera.orientate(x, y);
		if (mouseEvent->buttons() & Qt::MiddleButton)
			camera.move(x, y);
		if (mouseEvent->buttons() & Qt::RightButton)
			camera.move(x, y);
		break;
	case Release:
		break;
	default:
		break;
	}
}
