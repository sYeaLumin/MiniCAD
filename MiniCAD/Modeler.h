#pragma once
#include <vector>
#include <QOpenGLFunctions>
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
	void draw(LShaderProgram & shader);
	bool addNewSolid(shared_ptr<Solid>& s);
	void testModelCube();

private:
	shared_ptr<Solid> solidList;
	EulerOperator eulerOP;
	vector<Point> vertexData;
	vector<vector<vector<Point>>> faceData;
};

