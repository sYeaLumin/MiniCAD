#include "DataStructure.h"
using namespace CAD;

CAD::Solid::Solid()
{
	static int id = 0;
	sID = id++;
}

shared_ptr<Vertex> CAD::Solid::findV(const Point p)
{
	shared_ptr<Vertex> tmp = sVertexs;
	for (; tmp; tmp = tmp->next)
		if (Compare::vv(tmp->p, p))
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

bool CAD::Loop::addHE(shared_ptr<HalfEdge>& he)
{
	if (!he)
		return false;
	if (!lHalfEdges)
		lHalfEdges = he;
	else {
		shared_ptr<HalfEdge> tmp = lHalfEdges;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = he;
		he->prev = tmp;
	}
	return true;
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

bool CAD::Compare::vv(const Point & p1, const Point & p2)
{
	for (size_t i = 0; i < 3; i++) 
		if ((p1.pos[i] - p1.pos[i]) > MINERROR)
			return false;
	return true;
}
