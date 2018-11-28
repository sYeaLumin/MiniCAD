#pragma once
#include <vector>
#include <QOpenGLFunctions>
#include <qdebug.h>
#include "DataStructure.h"
#include "EulerOperator.h"
#include "miniCDT.h"
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
	void draw(LShaderProgram & shader);
	void drawLine(LShaderProgram & shader);
	void setupLineData();
	void setupLineDataTest1();
	void setupLineDataTest2();
	void setupLineDataTestCDT1();
	bool addNewSolid(shared_ptr<Solid>& s);
	void testModelCube();
	void testModelCube2();
	void testModelCubeWithHole();
	void testModelCubeWithHole2();

private:
	shared_ptr<Solid> solidList;
	EulerOperator eulerOP;
	vector<Point> vertexData;
	vector<vector<vector<Point>>> faceData;
};

