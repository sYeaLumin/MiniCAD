#pragma once
#include<iostream>
#include <memory>
#include <vector>
#include <qdebug.h>
#include <glm.hpp>
#include "DataStructure.h"

namespace CAD {
	class Tri {
	public:
		int v[3];
		weak_ptr<Tri> adjTri[3];
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
		vector<glm::vec3> vList;
		vector<Tri> triList;
		vector<vector<constraintEdge>> boundary;

	public:
		void init(shared_ptr<Face>& face)
		{
			boundary.clear();
			shared_ptr<Loop> currLoop = face->fLoops;
			shared_ptr<HalfEdge> currHE;
			for (; currLoop; currLoop = currLoop->next) {
				currHE = currLoop->lHalfEdges;
				pList.push_back(currHE->startVertex->p);
				int startIdx = pList.size() - 1;
				vector<constraintEdge> conE;
				currHE = currHE->next;
				while (currHE != currLoop->lHalfEdges)
				{
					pList.push_back(currHE->startVertex->p);
					conE.push_back(constraintEdge(pList.size() - 2, pList.size() - 1));
					currHE = currHE->next;
				}
				conE.push_back(constraintEdge(pList.size() - 1, startIdx));
				boundary.push_back(conE);
			}

			Point tmp1 = pList[1] - pList[0];
			Point tmp2 = pList[2] - pList[1];
			normal = glm::cross(
				glm::vec3(tmp1.pos[0], tmp1.pos[1], tmp1.pos[2]),
				glm::vec3(tmp2.pos[0], tmp2.pos[1], tmp2.pos[2])
			);
		}

		void Triangulate() 
		{

		}
	};

}
