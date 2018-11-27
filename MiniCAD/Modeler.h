#pragma once
#include <vector>
#include <QOpenGLFunctions>
#include <qdebug.h>
#include "DataStructure.h"
#include "EulerOperator.h"
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
	void setupLineData2();
	bool addNewSolid(shared_ptr<Solid>& s);
	void testModelCube();
	void testModelCubeWithHole();

private:
	shared_ptr<Solid> solidList;
	EulerOperator eulerOP;
	vector<Point> vertexData;
	vector<vector<vector<Point>>> faceData;
};

