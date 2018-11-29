#pragma once
#include<iostream>
#include <memory>
#include <vector>
#include <random>
#include <qdebug.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "DataStructure.h"

namespace CAD {
	class Tri {
	public:
		int v[3];
		shared_ptr<Tri> adjTri[3];
		Tri() {}
		Tri(int v1, int v2, int v3) {
			v[0] = v1;
			v[1] = v2;
			v[2] = v3;
		}
		bool ifSameTri(Tri & t) {
			if (v[0] == t.v[0] && v[1] == t.v[1] && v[2] == t.v[2])
				return true;
			return false;
		}
		bool ifSameTri(shared_ptr<Tri> & t) {
			if (v[0] == t->v[0] && v[1] == t->v[1] && v[2] == t->v[2])
				return true;
			return false;
		}
		void changeAdj(Tri & t1, Tri & t2) {
			for (size_t i = 0; i<3; i++)
				if (adjTri[i]->ifSameTri(t1))
					adjTri[i] = make_shared<Tri>(t2);
		}
	};
	class constraintEdge {
	public:
		int v[2];
		constraintEdge(int v1, int v2) {
			v[0] = v1;
			v[1] = v2;
		}
	};
	class miniCDT
	{
	private:
		glm::vec3 normal;
		vector<Point> pList;
		vector<glm::vec2> vList;
		vector<Tri> triList;
		vector<vector<constraintEdge>> boundary;

	private:
		glm::vec3 front, right;
		glm::vec3 cEye, cCenter, cUp;
		glm::mat4 viewMat;

		default_random_engine randE;

	public:
		void init(shared_ptr<Face>& face);

		void Triangulate();

		void setUpLineDataTest1(vector<Point>& vertexData);

	private:
		bool ifOnEdge(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p);
		void addOnEdge(Tri & t, int e, int v);
	};

}
