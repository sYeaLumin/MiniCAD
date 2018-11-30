#include "MiniCADWidget.h"



MiniCADWidget::MiniCADWidget(QWidget *parent) :
	QOpenGLWidget(parent),
	camera(),
	Lineshader(LineVSPath, LineFSPath, camera),
	Faceshader(FaceVSPath, FaceFSPath, camera)
{
	//modeler.testModelCube2();
	//modeler.testModelCubeWithHole2();
	//modeler.testModelCubeWithHole3();
	//modeler.testModel();
	modeler.testModelData();
}


MiniCADWidget::~MiniCADWidget()
{
}

QString MiniCADWidget::subfacePointShowData()
{
	string show("Subface Point : \n");
	show += string("Face Out Loop : \n");
	for (size_t i = 0; i < modeler.subFace.size(); i++) {
		string mes = "F : ";
		for (size_t k = 0; k < 3; k++) {
			string tmp = to_string(modeler.subFace[i].pos[k]);
			tmp = tmp.substr(0, tmp.size() - 4);
			mes += tmp;
			mes += " ";
		}
		show += mes;
		show += "\n";
	}
	show += string("\n");

	show += string("Face In Loop : \n");
	for (size_t i = 0; i < modeler.subHoles.size(); i++) {
		vector<Point> subHoleCurr = modeler.subHoles[i];
		for (size_t j = 0; j < subHoleCurr.size(); j++) {
			string mes = "H : ";
			for (size_t k = 0; k < 3; k++) {
				string tmp = to_string(subHoleCurr[j].pos[k]);
				tmp = tmp.substr(0, tmp.size() - 4);
				mes += tmp;
				mes += " ";
			}
			show += mes;
			show += "\n";
		}
		show += string("\n");
	}

	show += string("Current subHole : \n");
	for (size_t i = 0; i < modeler.subHoleCurr.size(); i++) {
		string mes = "H : ";
		for (size_t k = 0; k < 3; k++) {
			string tmp = to_string(modeler.subHoleCurr[i].pos[k]);
			tmp = tmp.substr(0, tmp.size() - 4);
			mes += tmp;
			mes += " ";
		}
		show += mes;
		show += "\n";
	}
	show += string("\n");

	//qDebug() << show.c_str();
	return QString(show.c_str());
}

void MiniCADWidget::changeDrawType(int type)
{
	makeCurrent();
	switch (type)
	{
	case 0:
		ifDrawLines = true;
		ifDrawFace = false;
		modeler.setupLineData();
		break;
	case 1:
		break;
	case 2:
		ifDrawLines = false;
		ifDrawFace = true;
		modeler.setupFaceData();
		break;
	default:
		break;
	}
	update();
}

void MiniCADWidget::modelSubfaceBuild()
{
	makeCurrent();
	modeler.testModel();
	if (ifDrawLines)
		modeler.setupLineData();
	if (ifDrawFace)
		modeler.setupFaceData();
	update();
}

void MiniCADWidget::modelSubfaceReset()
{
	modeler.subFace.clear();
	modeler.subHoleCurr.clear();
	modeler.subHoles.clear();
}

void MiniCADWidget::modelSubfaceAddOutLoopPoint(float x, float y, float z)
{
	modeler.subFace.push_back(Point(x, y, z));
}

void MiniCADWidget::modelSubfaceAddInLoopPoint(float x, float y, float z)
{
	modeler.subHoleCurr.push_back(Point(x, y, z));
}

void MiniCADWidget::modelSubfaceNewInLoopPoint()
{
	modeler.subHoles.push_back(modeler.subHoleCurr);
	modeler.subHoleCurr.clear();
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

void MiniCADWidget::buttonSweep(float x, float y, float z, float l)
{
	qDebug() << "		x : " << x << " y : " << y << " z : " << z << "l : " << l;
	makeCurrent();
	modeler.doSweep(x, y, z, l);
	if (ifDrawLines)
		modeler.setupLineData();
	if (ifDrawFace)
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
