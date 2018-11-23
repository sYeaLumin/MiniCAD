#pragma once
#include<iostream>
#include <memory>
#include "DataStructure.h"
using namespace std;
using namespace CAD;

class EulerOperator
{
public:
	EulerOperator();
	~EulerOperator();

	shared_ptr<Solid> mvfs(const Point p);
	shared_ptr<HalfEdge> mev(const Point p1,const Point p2, shared_ptr<Loop>& lp);
	shared_ptr<Loop> mef(const Point p1, const Point p2, shared_ptr<Loop>& lp);

private:
	shared_ptr<Solid> nowSolid;
};

