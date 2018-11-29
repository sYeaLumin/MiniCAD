#pragma once
#include<iostream>
#include <memory>
#include <vector>
#include <random>
#include <set>
#include <qdebug.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "DataStructure.h"
#include "ModelRenderingObject.h"

namespace CAD {
	class Tri {
	public:
		int v[3];
		weak_ptr<Tri> adjTri[3];
		Tri() {}
		Tri(int v1, int v2, int v3) {
			v[0] = v1;
			v[1] = v2;
			v[2] = v3;
		}
		bool ifSameTri(shared_ptr<Tri> & t) {
			if (v[0] == t->v[0] && v[1] == t->v[1] && v[2] == t->v[2])
				return true;
			return false;
		}
		void changeAdj(shared_ptr<Tri> & t1, shared_ptr<Tri> & t2) {
			for (size_t i = 0; i < 3; i++)
				if (adjTri[i].lock()  &&  adjTri[i].lock()->ifSameTri(t1))
					adjTri[i] = t2;
		}
	};

	class Circle {
	public:
		glm::vec2 c;
		float r;
		Circle(glm::vec2 p1, glm::vec2 p2) {
			c = (p1 - p2) / 2.0f;
			r = glm::length(p1 - p2) / 2.0;
		}
		Circle(glm::vec2 pt1, glm::vec2 pt2, glm::vec2 pt3) {
			float A1, A2, B1, B2, C1, C2, temp;
			A1 = pt1.x - pt2.x;
			B1 = pt1.y - pt2.y;
			C1 = (pow(pt1.x, 2) - pow(pt2.x, 2) + pow(pt1.y, 2) - pow(pt2.y, 2)) / 2;
			A2 = pt3.x - pt2.x;
			B2 = pt3.y - pt2.y;
			C2 = (pow(pt3.x, 2) - pow(pt2.x, 2) + pow(pt3.y, 2) - pow(pt2.y, 2)) / 2;
			temp = A1*B2 - A2*B1;
			//判断三点是否共线
			if (temp == 0) {//共线则将第一个点pt1作为圆心
				c.x = pt1.x;
				c.y = pt1.y;
			}
			else {//不共线则求出圆心：
				c.x = (C1*B2 - C2*B1) / temp;
				c.y = (A1*C2 - A2*C1) / temp;
			}
			r = sqrtf((c.x - pt1.x)*(c.x - pt1.x) + (c.y - pt1.y)*(c.y - pt1.y));
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
		bool ifLog = false;
		glm::vec3 normal;
		vector<Point> pList;
		vector<glm::vec2> vList;
		vector<shared_ptr<Tri>> triList;
		vector<vector<constraintEdge>> boundary;

	private:
		glm::vec3 front, right;
		glm::vec3 cEye, cCenter, cUp;
		glm::mat4 viewMat;

		default_random_engine randE;

	public:
		void init(shared_ptr<Face>& face);
		void Triangulate();

		void Log();
		void setUpLineDataTest1(vector<Point>& vertexData);
		void setUpLineDataTest2(vector<Point>& vertexData);
		void setUpFaceData(ModelRenderingObject & rObj);

	private:
		bool ifOnEdge(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p);
		void addOnEdge(shared_ptr<Tri> t, int e, int v);
		bool ifInTriangle(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p3, glm::vec2 & p);
		void addInTri(shared_ptr<Tri> & t, int v);

		bool ifInCircle(Circle & c, glm::vec2 & p);
		bool ifBEdge(int v1, int v2);
		void swapTest(shared_ptr<Tri> & t, int e);

		void removeTri(shared_ptr<Tri> & t);
		int orientation(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p3);

		void deleteTriInHole();
	};

}
