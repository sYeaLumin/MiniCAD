#include "DataStructure.h"
#include <math.h>
using namespace CAD;


bool Comparevv(const Point& p1, const Point& p2) {
	for (size_t i = 0; i < 3; i++)
		if (abs(p1.pos[i] - p2.pos[i]) > MINERROR)
			return false;
	return true;
}

CAD::Solid::Solid()
{
	static int id = 0;
	sID = id++;
}

shared_ptr<Vertex> CAD::Solid::findV(Point p)
{
	shared_ptr<Vertex> tmp = sVertexs;
	for (; tmp; tmp = tmp->next)
		if (Comparevv(tmp->p, p))
			return tmp;
	return nullptr;
}

bool CAD::Solid::addF(shared_ptr<Face>& face)
{
	if (!face)
		return false;
	if (!sFaces)
		sFaces = face;
	else {
		shared_ptr<Face> tmp = sFaces;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = face;
		face->prev = tmp;
	}
	return true;
}

bool CAD::Solid::addE(shared_ptr<Edge>& edge)
{
	if (!edge)
		return false;
	if (!sEdges)
		sEdges = edge;
	else {
		shared_ptr<Edge> tmp = sEdges;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = edge;
		edge->prev = tmp;
	}
	return true;
}

bool CAD::Solid::addV(shared_ptr<Vertex>& vertex)
{
	if (!vertex)
		return false;
	if (!sVertexs)
		sVertexs = vertex;
	else {
		shared_ptr<Vertex> tmp = sVertexs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = vertex;
		vertex->prev = tmp;
	}
	return true;
}

bool CAD::Solid::deleteE(shared_ptr<Edge>& edge)
{
	edge->leftHE = nullptr;
	edge->rightHE = nullptr;

	if (edge->next && edge->prev) {
		edge->prev->next = edge->next;
		edge->next->prev = edge->prev;
	}
	else if (edge->next && !edge->prev) {
		sEdges = edge->next;
	}
	else if (!edge->next && edge->prev) {
		edge->prev->next = nullptr;
	}
	else {
		sEdges = nullptr;
	}
	return true;
}

bool CAD::Solid::deleteF(shared_ptr<Face>& face)
{
	face->fLoops = nullptr;
	if (face->next && face->prev) {
		face->prev->next = face->next;
		face->next->prev = face->prev;
	}
	else if (face->next && !face->prev) {
		sFaces = face->next;
	}
	else if (!face->next && face->prev) {
		face->prev->next = nullptr;
	}
	else {
		sFaces = nullptr;
	}
	return true;
}

CAD::Face::Face()
{
	static int id = 0;
	fID = id++;
}

bool CAD::Face::addL(shared_ptr<Loop>& lp)
{
	if (!lp)
		return false;
	if (!fLoops)
		fLoops = lp;
	else {
		shared_ptr<Loop> tmp = fLoops;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lp;
		lp->prev = tmp;
	}
	return true;
}

CAD::Loop::Loop()
{
	static int id = 0;
	lID = id++;
}

shared_ptr<HalfEdge> CAD::Loop::findHE(const shared_ptr<Vertex> & v)
{
	if (!lHalfEdges)
		return nullptr;
	shared_ptr<HalfEdge> hetmp = lHalfEdges;
	do {
		if (hetmp->startVertex == v)
			return hetmp;
		hetmp = hetmp->next;
	} while (hetmp != lHalfEdges);
	return nullptr;
}

shared_ptr<HalfEdge> CAD::Loop::findHE(const shared_ptr<Vertex>& v1, const shared_ptr<Vertex>& v2)
{
	if (!lHalfEdges)
		return nullptr;
	shared_ptr<HalfEdge> hetmp = lHalfEdges;
	do {
		if (hetmp->startVertex == v1 && hetmp->next->startVertex == v2)
			return hetmp;
		hetmp = hetmp->next;
	} while (hetmp != lHalfEdges);
	return nullptr;
}

CAD::HalfEdge::HalfEdge()
{
	static int id = 0;
	heID = id++;
}

CAD::Edge::Edge()
{
	static int id = 0;
	eID = id++;
}
