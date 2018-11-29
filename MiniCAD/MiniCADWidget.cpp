#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	camera(),
	Lineshader(LineVSPath, LineFSPath, camera),
	Faceshader(FaceVSPath, FaceFSPath, camera)
{
	//modeler.testModelCube2();
	//modeler.testModelCubeWithHole2();
	modeler.testModelCubeWithHole3();
}


MiniCADWidget::~MiniCADWidget()
{
}

void MiniCADWidget::initializeGL()
{
	initializeOpenGLFunctions();
	camera.init(geometry().width(), geometry().height());
	modeler.init();
	Lineshader.init();
	Faceshader.init();
	glViewport(0, 0, geometry().width(), geometry().height());//?
	glEnable(GL_MULTISAMPLE);

	if(ifDrawLines)
		modeler.setupLineData();
	if(ifDrawFace)
		modeler.setupFaceData();
}

void MiniCADWidget::paintGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw
	if (ifDrawLines)
		modeler.drawLine(Lineshader);
	if (ifDrawFace)
		modeler.drawFace(Faceshader);
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

void MiniCADWidget::onDrawLinesCheckBoxSlot(bool checkState) {
	makeCurrent();
	ifDrawLines = checkState;
	modeler.setupLineData();
	update();
}

void MiniCADWidget::onDrawFacesCheckBoxSlot(bool checkState)
{
	makeCurrent();
	ifDrawFace = checkState;
	modeler.setupFaceData();
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
