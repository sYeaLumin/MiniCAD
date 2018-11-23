#include "EulerOperator.h"

EulerOperator::EulerOperator()
{
}


EulerOperator::~EulerOperator()
{
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
		cout << "FUNC mev : Can't find vertex1 in Solid " << nowSolid->sID << endl;
		return nullptr;
	}
	shared_ptr<Edge> newEdge = make_shared<Edge>();
	shared_ptr<HalfEdge> he1 = make_shared<HalfEdge>();
	shared_ptr<HalfEdge> he2 = make_shared<HalfEdge>();
	shared_ptr<Vertex> v2 = make_shared<Vertex>(p2);

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
			cout << "FUNC mev : Can't find vertex1 in Loop " << lp->lID << endl;
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
		cout << "FUNC mef : Can't find vertex1 in Solid " << nowSolid->sID << endl;
		return nullptr;
	}
	shared_ptr<Vertex> v2 = nowSolid->findV(p2);
	if (!v2) {
		cout << "FUNC mev : Can't find vertex2 in Solid " << nowSolid->sID << endl;
		return nullptr;
	}
	shared_ptr<HalfEdge> heInsert1 = lp->findHE(v1);
	if (!heInsert1) {
		cout << "FUNC mev : Can't find vertex1 in Loop " << lp->lID << endl;
		return nullptr;
	}
	shared_ptr<HalfEdge> heInsert2 = lp->findHE(v2);
	if (!heInsert2) {
		cout << "FUNC mev : Can't find vertex2 in Loop " << lp->lID << endl;
		return nullptr;
	}

	shared_ptr<Face> newFace = make_shared<Face>();
	shared_ptr<Loop> newLoop = make_shared<Loop>();
	shared_ptr<Edge> newEdge = make_shared<Edge>();
	shared_ptr<HalfEdge> he1 = make_shared<HalfEdge>();
	shared_ptr<HalfEdge> he2 = make_shared<HalfEdge>();
	
	newLoop->addHE(he2); // ! 
	//环接：V1顶点
	heInsert1->prev->next = he2;
	he2->prev = heInsert1->prev;
	heInsert1->prev = he1;
	he1->next = heInsert1;
	//环接：修改newLoop内HE的Loop连接
	shared_ptr<HalfEdge> tmp = heInsert2;
	for (; tmp; tmp = tmp->next)
		tmp->heLoop = newLoop;
	//环接：V2顶点
	heInsert2->prev->next = he1;
	he1->prev = heInsert2->prev;
	heInsert2->prev = he2;
	he2->next = heInsert2;
	
	//新边设置
	he1->startVertex = v2;
	he2->startVertex = v1;
	he1->adj = he2;
	he2->adj = he1;
	he1->heEdge = he2->heEdge = newEdge;
	newEdge->leftHE = he1;
	newEdge->rightHE = he2;

	//上下层连接
	nowSolid->addF(newFace);
	newFace->fSolid = nowSolid;
	newFace->addL(newLoop);
	newLoop->lFace = newFace;

	return newLoop;
}
