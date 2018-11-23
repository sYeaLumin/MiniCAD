#pragma once
#include <QOpenGLFunctions>
#include "DataStructure.h"
#include "EulerOperator.h"
using namespace CAD;

class Modeler :
	public QObject, protected QOpenGLFunctions
{
public:
	Modeler();
	~Modeler();
};

