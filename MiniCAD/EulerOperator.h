#pragma once
#include<iostream>
#include <memory>
#include <qdebug.h>
#include "DataStructure.h"
using namespace std;
using namespace CAD;

class EulerOperator
{
public:
	EulerOperator();
	~EulerOperator();

	void sweep(shared_ptr<Face>& face, Point dir, float dist);
	shared_ptr<Solid> mvfs(const Point & p);
	shared_ptr<HalfEdge> mev(const Point & p1,const Point & p2, shared_ptr<Loop>& lp);
	shared_ptr<Loop> mef(const Point & p1, const Point & p2, shared_ptr<Loop>& lp);
	shared_ptr<Loop> kemr(const Point & p1, const Point & p2, shared_ptr<Loop> & lp);
	void kfmrh(shared_ptr<Loop>& lp1, shared_ptr<Loop>& lp2);

private:
	shared_ptr<Solid> nowSolid;
};

