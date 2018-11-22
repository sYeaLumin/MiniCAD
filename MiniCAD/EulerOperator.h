#pragma once

#include <memory>
#include "DataStructure.h"
using namespace std;
using namespace CAD;

class EulerOperator
{
public:
	EulerOperator();
	~EulerOperator();



private:
	shared_ptr<Solid> nowSolid;
};

