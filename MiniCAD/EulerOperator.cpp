#include "EulerOperator.h"

EulerOperator::EulerOperator()
{
}


EulerOperator::~EulerOperator()
{
}

void EulerOperator::sweep(shared_ptr<Face>& face, Point dir, float dist)
{
	dir.normalize();
	Point sweepLine = dir * dist;
	bool ifOutLoop = true;
	shared_ptr<Loop> currLoop = face->fLoops;
	shared_ptr<Loop> newOutLoop;
	shared_ptr<Loop> newInLoop;
	for (; currLoop != nullptr; currLoop = currLoop->next) {
		shared_ptr<HalfEdge> currHE = currLoop->lHalfEdges;
		shared_ptr<HalfEdge> nextHE = currHE->next;
		shared_ptr<HalfEdge> prevHE = currHE->prev;
		shared_ptr<Vertex> startV = currHE->startVertex;
		shared_ptr<Vertex> currV = currHE->startVertex;
		Point startSweepP = currV->p + sweepLine;
		Point newSweepP = startSweepP;
		Point lastSweepP;
		shared_ptr<HalfEdge> tmp = currLoop->lHalfEdges;
		for (; tmp->next != currLoop->lHalfEdges; tmp = tmp->next) {
			qDebug() << tmp->heID << " : " << tmp->startVertex->vID;
		}
		qDebug() << tmp->heID << " : " << tmp->startVertex->vID;
		mev(currV->p, newSweepP, currLoop);
		qDebug() << "FUNC sweep : currLoop->lHalfEdges ID " << currHE->heID;
		do
		{
			prevHE = currHE;
			currHE = nextHE;
			nextHE = currHE->next;
			currV = currHE->startVertex;
			lastSweepP = newSweepP;
			newSweepP = currV->p + sweepLine;
			mev(currV->p, newSweepP, currLoop);
			mef(lastSweepP, newSweepP, currLoop);
			qDebug() << "FUNC sweep : currHE ID " << currHE->heID;
			qDebug() << "FUNC sweep : nextHE ID " << nextHE->heID;
		} while (nextHE->startVertex != startV);
		if (ifOutLoop) {
			ifOutLoop = false;
			newOutLoop = mef(newSweepP, startSweepP, currLoop);
		}
		else {
			newInLoop = mef(newSweepP, startSweepP, currLoop);
			kfmrh(newOutLoop, newInLoop);
		}
	}
}

void EulerOperator::sweep(vector<shared_ptr<Loop>> LoopList, Point dir, float dist)
{
	dir.normalize();
	Point sweepLine = dir * dist;
	shared_ptr<Loop> newOutLoop;
	shared_ptr<Loop> newInLoop;
	newOutLoop = _sweep(LoopList[0], dir, dist);
	for (size_t i = 1; i < LoopList.size(); i++) {
		newInLoop = _sweep(LoopList[i], dir, dist);
		kfmrh(newOutLoop, newInLoop);
	}
}

shared_ptr<Loop> EulerOperator::_sweep(shared_ptr<Loop>& currLoop, Point dir, float dist)
{
	dir.normalize();
	Point sweepLine = dir * dist;
	shared_ptr<HalfEdge> currHE = currLoop->lHalfEdges;
	shared_ptr<HalfEdge> nextHE = currHE->next;
	shared_ptr<HalfEdge> prevHE = currHE->prev;
	shared_ptr<Vertex> startV = currHE->startVertex;
	shared_ptr<Vertex> currV = currHE->startVertex;
	Point startSweepP = currV->p + sweepLine;
	Point newSweepP = startSweepP;
	Point lastSweepP;

	shared_ptr<HalfEdge> tmp = currLoop->lHalfEdges;
	for (; tmp->next != currLoop->lHalfEdges; tmp = tmp->next) {
		qDebug() << tmp->heID << " : " << tmp->startVertex->vID;
	}
	qDebug() << tmp->heID << " : " << tmp->startVertex->vID;
	mev(currV->p, newSweepP, currLoop);
	qDebug() << "FUNC sweep : currLoop->lHalfEdges ID " << currHE->heID;
	do
	{
		prevHE = currHE;
		currHE = nextHE;
		nextHE = currHE->next;
		currV = currHE->startVertex;
		lastSweepP = newSweepP;
		newSweepP = currV->p + sweepLine;
		mev(currV->p, newSweepP, currLoop);
		mef(lastSweepP, newSweepP, currLoop);
		qDebug() << "FUNC sweep : currHE ID " << currHE->heID;
		qDebug() << "FUNC sweep : nextHE ID " << nextHE->heID;
	} while (nextHE->startVertex != startV);

	return mef(newSweepP, startSweepP, currLoop);
}

shared_ptr<Solid> EulerOperator::mvfs(const Point& p)
{
	nowSolid = make_shared<Solid>();
	shared_ptr<Face> newFace = make_shared<Face>();
	shared_ptr<Loop> newLoop = make_shared<Loop>();
	shared_ptr<Vertex> newVertex = make_shared<Vertex>(p);

	nowSolid->addF(newFace);
	nowSolid->addV(newVertex);
	newFace->fSolid = nowSolid;
	newFace->addL(newLoop);
	newLoop->lFace = newFace;

	return nowSolid;
}

shared_ptr<HalfEdge> EulerOperator::mev(const Point& p1, const Point& p2, shared_ptr<Loop>& lp)
{
	shared_ptr<Vertex> v1 = nowSolid->findV(p1);
	if (!v1) {
		qDebug() << "FUNC mev : Can't find vertex1 in Solid " << nowSolid->sID;
		return nullptr;
	}
	qDebug() << "FUNC mev : Find vertex1 in Solid " << nowSolid->sID << " With ID " << v1->vID;
	shared_ptr<Edge> newEdge = make_shared<Edge>();
	shared_ptr<HalfEdge> he1 = make_shared<HalfEdge>();
	shared_ptr<HalfEdge> he2 = make_shared<HalfEdge>();
	shared_ptr<Vertex> v2 = make_shared<Vertex>(p2);
	qDebug() << "FUNC mev : New HalfEdge he1 ID " << he1->heID;
	qDebug() << "FUNC mev : New HalfEdge he2 ID " << he2->heID;
	//环接
	he1->next = he2;
	he2->prev = he1;
	shared_ptr<HalfEdge> hetmp = lp->lHalfEdges;
	if (!hetmp) {
		lp->lHalfEdges = he1;
		he1->prev = he2;
		he2->next = he1;
	}
	else {
		shared_ptr<HalfEdge> heInsert = lp->findHE(v1);
		if (!heInsert) {
			qDebug() << "FUNC mev : Can't find vertex1 in Loop " << lp->lID;
			return nullptr;
		}
		he1->prev = heInsert->prev;
		he2->next = heInsert;
		heInsert->prev->next = he1;
		heInsert->prev = he2;
	}
	he1->heLoop = he2->heLoop = lp;

	//新边设置
	he1->startVertex = v1;
	he1->adj = he2;
	he2->startVertex = v2;
	he2->adj = he1;
	he1->heEdge = he2->heEdge = newEdge;
	newEdge->leftHE = he1;
	newEdge->rightHE = he2;

	//上下层连接
	nowSolid->addE(newEdge);
	nowSolid->addV(v2);

	return he1;
}

shared_ptr<Loop> EulerOperator::mef(const Point& p1, const Point& p2, shared_ptr<Loop>& lp)
{
	shared_ptr<Vertex> v1 = nowSolid->findV(p1);
	if (!v1) {
		qDebug() << "FUNC mef : Can't find vertex1 in Solid " << nowSolid->sID;
		return nullptr;
	}
	shared_ptr<Vertex> v2 = nowSolid->findV(p2);
	if (!v2) {
		qDebug() << "FUNC mef : Can't find vertex2 in Solid " << nowSolid->sID;
		return nullptr;
	}
	shared_ptr<HalfEdge> heInsert1 = lp->findHE(v1);
	if (!heInsert1) {
		qDebug() << "FUNC mef : Can't find vertex1 in Loop " << lp->lID;
		return nullptr;
	}
	qDebug() << "FUNC mef : heInsert1 ID " << heInsert1->heID;
	shared_ptr<HalfEdge> heInsert2 = lp->findHE(v2);
	if (!heInsert2) {
		qDebug() << "FUNC mef : Can't find vertex2 in Loop " << lp->lID;
		return nullptr;
	}
	qDebug() << "FUNC mef : heInsert2 ID " << heInsert2->heID;

	shared_ptr<Face> newFace = make_shared<Face>();
	shared_ptr<Loop> newLoop = make_shared<Loop>();
	shared_ptr<Edge> newEdge = make_shared<Edge>();
	shared_ptr<HalfEdge> he1 = make_shared<HalfEdge>();
	shared_ptr<HalfEdge> he2 = make_shared<HalfEdge>();
	
	//newLoop->addHE(he2); 
	lp->lHalfEdges = he1;//！！！
	newLoop->lHalfEdges = he2;
	//环接：V1顶点
	heInsert1->prev->next = he1;
	he2->prev = heInsert2->prev;
	heInsert1->prev = he2;
	he2->next = heInsert1;
	//环接：修改newLoop内HE的Loop连接
	shared_ptr<HalfEdge> tmp = he2;
	for (; tmp; tmp = tmp->next)
		tmp->heLoop = newLoop;
	//环接：V2顶点
	heInsert2->prev->next = he2;
	he1->prev = heInsert1->prev;
	heInsert2->prev = he1;
	he1->next = heInsert2;
	
	//新边设置
	he1->startVertex = v1;
	he2->startVertex = v2;
	he1->adj = he2;
	he2->adj = he1;
	he1->heEdge = he2->heEdge = newEdge;
	newEdge->leftHE = he1;
	newEdge->rightHE = he2;

	//上下层连接
	nowSolid->addF(newFace);
	nowSolid->addE(newEdge);
	newFace->fSolid = nowSolid;
	newFace->addL(newLoop);
	newLoop->lFace = newFace;

	return newLoop;
}

shared_ptr<Loop> EulerOperator::kemr(const Point & p1, const Point & p2, shared_ptr<Loop>& lp)
{
	shared_ptr<Vertex> v1 = nowSolid->findV(p1);
	if (!v1) {
		qDebug() << "FUNC kemr : Can't find vertex1 in Solid " << nowSolid->sID;
		return nullptr;
	}
	shared_ptr<Vertex> v2 = nowSolid->findV(p2);
	if (!v2) {
		qDebug() << "FUNC kemr : Can't find vertex2 in Solid " << nowSolid->sID;
		return nullptr;
	}
	shared_ptr<HalfEdge> heDelete1 = lp->findHE(v1, v2);
	if (!heDelete1) {
		qDebug() << "FUNC kemr : Can't find vertex1 in Loop " << lp->lID;
		return nullptr;
	}
	shared_ptr<HalfEdge> heDelete2 = lp->findHE(v2, v1);
	if (!heDelete2) {
		qDebug() << "FUNC kemr : Can't find vertex2 in Loop " << lp->lID;
		return nullptr;
	}
	
	//删除边
	shared_ptr<Edge> deleteEdge = heDelete1->heEdge.lock();
	if (deleteEdge == nullptr)
	{
		qDebug() << "FUNC kemr : Edge with v" << v1->vID << " & v"<< v2->vID << " has already deleted !";
		return nullptr;
	}
	nowSolid->deleteE(deleteEdge);

	//v1点处半边连接
	if (heDelete2->next == heDelete1) {
		heDelete1->prev = nullptr;
		heDelete2->next = nullptr;
	}
	else {
		heDelete1->prev->next = heDelete2->next;
		heDelete2->next->prev = heDelete1->prev;
	}
	//v2点处半边连接
	shared_ptr<Loop> newLoop = make_shared<Loop>();
	if (heDelete1->next == heDelete2) {
		heDelete1->next = nullptr;
		heDelete2->prev = nullptr;
		newLoop->prev = lp;
		newLoop->lFace = lp->lFace;
		newLoop->next = nullptr;
		newLoop->lHalfEdges = nullptr;
	}
	else {
		heDelete1->next->prev = heDelete2->prev;
		heDelete2->prev->next = heDelete1->next;
		shared_ptr<HalfEdge> tmp = heDelete1->next;
		do
		{
			tmp->heLoop = newLoop;
			tmp = tmp->next;
		} while (tmp->startVertex != v2);
	}
	heDelete1 = heDelete2 = nullptr;
	
	return newLoop;
}

void EulerOperator::kfmrh(shared_ptr<Loop>& lpOut, shared_ptr<Loop>& lpIn)
{
	if (!lpOut || !lpIn) {
		qDebug() << "FUNC kfmerh : illegal Loop " << (lpOut ? "IpIn": "IpOut");
		return;
	}
	shared_ptr<Face> currFace = lpOut->lFace.lock();
	if (currFace == nullptr) {
		qDebug() << "FUNC kfmerh : lpOut->Face is illegal !";
		return;
	}
	shared_ptr<Face> deleteFace = lpIn->lFace.lock();
	if (deleteFace == nullptr) {
		qDebug() << "FUNC kfmerh : THe face of lpIn has already deleted !";
		return;
	}
	//加环
	currFace->addL(lpIn);
	//删面
	nowSolid->deleteF(deleteFace);
	return;
}
