#pragma once
#include <memory>
#include <math.h>
#define MINERROR 10e-6
using namespace std;

namespace CAD{
	class Solid;
	class Face;
	class Loop;
	class HalfEdge;
	class Edge;
	class Vertex;
	class Point;

	class Solid {
	public:
		int sID;
		shared_ptr<Face> sFaces;
		shared_ptr<Edge> sEdges;
		shared_ptr<Vertex> sVertexs;
		shared_ptr<Solid> prev;
		shared_ptr<Solid> next;

		Solid();
		shared_ptr<Vertex> findV(Point p);
		bool addF(shared_ptr<Face>& face);
		bool addE(shared_ptr<Edge>& edge);
		bool addV(shared_ptr<Vertex>& vertex);
		bool deleteE(shared_ptr<Edge>& edge);
		bool deleteF(shared_ptr<Face> & face);
	};

	class Face {
	public:
		int fID;
		//double fNormal[3];
		weak_ptr<Solid> fSolid;
		shared_ptr<Loop> fLoops;
		shared_ptr<Face> prev;
		shared_ptr<Face> next;

		Face();
		bool addL(shared_ptr<Loop>& lp);
	};

	class Loop {
	public:
		int lID;
		weak_ptr<Face> lFace;
		shared_ptr<HalfEdge> lHalfEdges;
		shared_ptr<Loop> prev;
		shared_ptr<Loop> next;

		Loop();
		shared_ptr<HalfEdge> findHE(const shared_ptr<Vertex> & v);
		shared_ptr<HalfEdge> findHE(const shared_ptr<Vertex> & v1,
			const shared_ptr<Vertex> & v2);
	};

	class HalfEdge {
	public:
		int heID;
		weak_ptr<Loop> heLoop;
		weak_ptr<Edge> heEdge;
		shared_ptr<Vertex> startVertex;
		shared_ptr<HalfEdge> prev;
		shared_ptr<HalfEdge> next;
		weak_ptr<HalfEdge> adj;

		HalfEdge();
	};

	class Edge {
	public:
		int eID;
		shared_ptr<HalfEdge> leftHE;
		shared_ptr<HalfEdge> rightHE;
		shared_ptr<Edge> prev;
		shared_ptr<Edge> next;
		
		Edge();	
	};

	class Point {
	public:
		double pos[3];
		Point() {}
		Point(double x, double y, double z) {
			pos[0] = x;
			pos[1] = y;
			pos[2] = z;
		}
		Point(const Point &point) {
			pos[0] = point.pos[0];
			pos[1] = point.pos[1];
			pos[2] = point.pos[2];
		}
		Point& operator*(const double d) {
			return Point(pos[0] * d, pos[1] * d, pos[2] * d);
		}
		Point& operator+(const Point point) {
			return Point(pos[0] + point.pos[0], pos[1] + point.pos[1], pos[2] + point.pos[2]);
		}
		void normalize() {
			double norm = sqrt(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2]);
			pos[0] = pos[0] / norm;
			pos[1] = pos[1] / norm;
			pos[2] = pos[2] / norm;
		}
	};

	class Vertex {
	public:
		int vID;
		Point p;
		shared_ptr<Vertex> prev;
		shared_ptr<Vertex> next;

		Vertex(Point point) : p(point){
			static int id = 0;
			vID = id++;
		}
	};


}
