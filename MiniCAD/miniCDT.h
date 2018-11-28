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
		glm::vec3 n;
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
		vector<glm::vec2> vList;
		vector<Tri> triList;
		vector<vector<constraintEdge>> boundary;

	private:
		glm::vec3 front, right;
		glm::vec3 cEye, cCenter, cUp;
		glm::mat4 viewMat;

	public:
		void init(shared_ptr<Face>& face)
		{
			//添加点&边界约束
			pList.clear();
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
			//计算面的normal
			Point tmp1 = pList[1] - pList[0];
			Point tmp2 = pList[2] - pList[1];
			normal = glm::normalize(glm::cross(
				glm::vec3(tmp2.pos[0], tmp2.pos[1], tmp2.pos[2]),
				glm::vec3(tmp1.pos[0], tmp1.pos[1], tmp1.pos[2])
			));

			//投影到平面
			cCenter = glm::vec3(pList[0].pos[0], pList[0].pos[1], pList[0].pos[2]);
			cEye = cCenter + normal * float(tmp1.length());
			front = glm::normalize(cCenter - cEye);
			glm::vec3 worldUp = glm::vec3(tmp1.pos[0], tmp1.pos[1], tmp1.pos[2]);
			right = glm::normalize(glm::cross(front, worldUp));
			viewMat = glm::lookAt(cEye, cCenter, cUp);
			for (size_t i = 0; i < pList.size(); i++) {
				glm::vec4 oldP = glm::vec4(pList[i].pos[0], pList[i].pos[1], pList[i].pos[2], 1.0f);
				glm::vec2 newP = viewMat * oldP; //舍弃z轴量
				vList.push_back(newP);
			}
		}

		void Triangulate() 
		{
			bool* ifUse = new bool[vList.size()];
			triList.clear();
		}

		void setUpLineDataTest1(vector<Point>& vertexData) {
			qDebug() << "		normal : " << normal.x << " : " << normal.y << " : " << normal.z;
			Point offset(normal.x, normal.y, normal.z);
			double off = 0.2;
			for (size_t i = 0; i < boundary.size(); i++) {
				vector<constraintEdge> conEs = boundary[i];
				for (size_t j = 0; j < conEs.size(); j++) {
					Point newStartP = pList[conEs[j].v[0]] + offset * off;
					Point newEndP = pList[conEs[j].v[1]] + offset * off;
					vertexData.push_back(newStartP);
					vertexData.push_back(newEndP);
				}
				if (i == 0)
					off *= -1;
			}
		}


	};

}
