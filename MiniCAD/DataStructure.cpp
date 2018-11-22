#include "DataStructure.h"

CAD::Solid::Solid()
{
	static int id = 0;
	sID = id++;
}

CAD::Solid::~Solid()
{
}

CAD::Face::Face()
{
	static int id = 0;
	fID = id++;
}

CAD::Face::~Face()
{
}

CAD::Loop::Loop()
{
	static int id = 0;
	lID = id++;
}

CAD::Loop::~Loop()
{
}

CAD::HalfEdge::HalfEdge()
{
	static int id = 0;
	heID = id++;
}

CAD::HalfEdge::~HalfEdge()
{
}

CAD::Edge::Edge()
{
	static int id = 0;
	eID = id++;
}

CAD::Edge::~Edge()
{
}

CAD::Vertex::Vertex()
{
	static int id = 0;
	vID = id++;
}

CAD::Vertex::~Vertex()
{
}
