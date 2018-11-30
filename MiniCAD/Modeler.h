#pragma once
#include <vector>
#include <QOpenGLFunctions>
#include <qdebug.h>
#include "DataStructure.h"
#include "EulerOperator.h"
#include "miniCDT.h"
#include "ModelRenderingObject.h"
#include "LOpenGL\LShaderProgram.h"

using namespace std;
using namespace CAD;

class Modeler :
	public QObject, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	Modeler();
	~Modeler();
	void init();
	void drawLine(LShaderProgram & shader);
	void drawFace(LShaderProgram & shader);

	void setupLineData();
	void setupLineDataTest1();
	void setupLineDataTest2();
	void setupLineDataCDT();

	void setupFaceData();

	bool addNewSolid(shared_ptr<Solid>& s);
	void doSweep(float x, float y, float z, float l);

	void testModelCube();
	void testModelCube2();
	void testModelCubeWithHole();
	void testModelCubeWithHole2();
	void testModelCubeWithHole3();
	void testModel();
	void testModelData();

private:
	shared_ptr<Solid> solidList;
	EulerOperator eulerOP;
	vector<Point> vertexData;
	vector<vector<vector<Point>>> faceData;
	ModelRenderingObject mObj;
	vector<shared_ptr<Loop>> sweepLoopList;

public:
	vector<Point> subFace;
	vector<vector<Point>> subHoles;
	vector<Point> subHoleCurr;
};

