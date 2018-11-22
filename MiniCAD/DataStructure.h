#pragma once

#include<memory>
using namespace std;

namespace CAD{
	class Solid;
	class Face;
	class Loop;
	class HalfEdge;
	class Edge;
	class Vertex;

	class Solid {
	public:
		int sID;
		shared_ptr<Face> sFaces;
		shared_ptr<Edge> sEdges;
		shared_ptr<Vertex> sVertexs;
		shared_ptr<Solid> sPrev;
		shared_ptr<Solid> sNext;

		Solid();
		~Solid();
	};

	class Face {
	public:
		int fID;
		//double fNormal[3];
		weak_ptr<Solid> fSolid;
		shared_ptr<Loop> fLoops;
		shared_ptr<Face> fPrev;
		shared_ptr<Face> fNext;

		Face();
		~Face();
	};

	class Loop {
	public:
		int lID;
		weak_ptr<Face> lFace;
		shared_ptr<HalfEdge> lHalfEdges;
		shared_ptr<Loop> lPrev;
		shared_ptr<Loop> lNext;

		Loop();
		~Loop();
	};

	class HalfEdge {
	public:
		int heID;
		weak_ptr<Loop> heLoop;
		weak_ptr<Edge> heEdge;
		shared_ptr<Vertex> startVertex;
		shared_ptr<HalfEdge> hePrev;
		shared_ptr<HalfEdge> heNext;
		shared_ptr<HalfEdge> heAdj;

		HalfEdge();
		~HalfEdge();
	};

	class Edge {
	public:
		int eID;
		shared_ptr<HalfEdge> leftHE;
		shared_ptr<HalfEdge> rightHE;
		shared_ptr<Edge> ePrev;
		shared_ptr<Edge> eNext;

		Edge();
		~Edge();
	};

	class Vertex {
	public:
		int vID;
		double pos[3];
		shared_ptr<Vertex> vPrev;
		shared_ptr<Vertex> vNext;

		Vertex();
		~Vertex();
	};
}
