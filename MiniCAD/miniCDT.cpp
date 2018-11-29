#include "miniCDT.h"
#define MIN 1e-6
void CAD::miniCDT::init(shared_ptr<Face>& face)
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

void CAD::miniCDT::Triangulate()
{
	float MAX = 100000.0;
	int top, left, right;
	int size = pList.size();
	bool* ifUsed = new bool[size];
	for (size_t i = 0; i < pList.size(); i++) ifUsed[i] = false;
	triList.clear();

	top = vList.size();
	vList.push_back(glm::vec2(0.0f, MAX));
	left = vList.size();
	vList.push_back(glm::vec2(-MAX, -MAX));
	right = vList.size();
	vList.push_back(glm::vec2(MAX, -MAX));
	triList.push_back(Tri(top, left, right));

	uniform_int_distribution<int> Rand(0, size);
	for (size_t i = 0; i < size; i++) {
		int index = 0;
		int r = Rand(randE) % (size - i);

		// 随机找下一个要加入的点
		for (size_t j = 0, k = 0; j<size; j++) {
			if (!ifUsed[j]) {
				if (k == r) {
					index = j;
					ifUsed[index] = true;
					break;
				}
				else {
					k++;
				}
			}
		}

		bool onEdge = true;
		for (size_t j = 0; j < triList.size() && ifOnEdge; j++) {
			for (size_t k = 0; k < 3; k++) {
				if (ifOnEdge(vList[triList[j].v[k]], vList[triList[j].v[(k + 1) % 3]], vList[index])) {

				}
			}
		}

	}
}

void CAD::miniCDT::setUpLineDataTest1(vector<Point>& vertexData)
{
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

bool CAD::miniCDT::ifOnEdge(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p)
{
	float dis, dis1, dis2;
	dis = glm::distance(p1, p2);
	dis1 = glm::distance(p, p2);
	dis2 = glm::distance(p, p2);

	if (dis1 < MIN || dis2 < MIN)
		return true;
	if (dis1 > dis || dis2 > dis)
		return false;

	float a, b, c;
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p1.y * (p2.x - p1.x) -
		p1.x * (p2.y - p1.y);
	return (abs(a * p.x + b * p.y + c) < MIN);
}

void CAD::miniCDT::addOnEdge(Tri & t, int e, int v)
{
	int p, a, b, d = 0;
	shared_ptr<Tri> bp, pa, ad, db, next;

	next = t.adjTri[e];
	bp = t.adjTri[(e + 1) % 3];
	pa = t.adjTri[(e + 2) % 3];

	a = t.v[e];
	b = t.v[(e + 1) % 3];
	p = t.v[(e + 2) % 3];

	if (next == nullptr) {
		Tri newTri[2];
		newTri[0] = Tri(p, a, v);
		newTri[1] = Tri(p, v, b);

		newTri[0].adjTri[0] = pa;
		newTri[0].adjTri[2] = make_shared<Tri>(newTri[1]);//写法？
		if (bp != nullptr)
			bp->changeAdj(t, newTri[1]);

		newTri[1].adjTri[0] = make_shared<Tri>(newTri[0]);
		newTri[1].adjTri[2] = bp;
		if (bp != nullptr)
			bp->changeAdj(t, newTri[1]);

		size_t f;
		for (f = 0; f < triList.size(); f++)
			if (triList[f].ifSameTri(t))
				break;
		triList.erase(triList.begin() + f);
		for (size_t i = 0; i < 2; i++)
			triList.push_back(newTri[i]);
	}
	else {
		for (size_t i = 0; i < 3; i++) {
			if (next->v[i] != a && next->v[i] != b) {
				d = next->v[i];
				db = next->adjTri[i];
				ad = next->adjTri[(i + 2) % 3];
			}
			Tri newTri[4];
			newTri[0] = Tri(p, a, v);
			newTri[1] = Tri(p, v, b);
			newTri[2] = Tri(v, a, d);
			newTri[3] = Tri(v, d, b);

			newTri[0].adjTri[0] = pa;
			newTri[0].adjTri[1] = make_shared<Tri>(newTri[2]);
			newTri[0].adjTri[2] = make_shared<Tri>(newTri[1]);
			if (pa != nullptr)
				pa->changeAdj(t, newTri[0]);

			newTri[1].adjTri[0] = make_shared<Tri>(newTri[0]);
			newTri[1].adjTri[1] = make_shared<Tri>(newTri[3]);
			newTri[1].adjTri[2] = bp;
			if (bp != nullptr)
				bp->changeAdj(t, newTri[1]);

			newTri[2].adjTri[0] = make_shared<Tri>(newTri[0]);
			newTri[2].adjTri[1] = ad;
			newTri[2].adjTri[2] = make_shared<Tri>(newTri[3]);
			if (ad != nullptr)
				ad->changeAdj(t, newTri[2]);

			newTri[3].adjTri[0] = make_shared<Tri>(newTri[2]);
			newTri[3].adjTri[1] = db;
			newTri[3].adjTri[2] = make_shared<Tri>(newTri[1]);
			if (db != nullptr)
				db->changeAdj(t, newTri[3]);

			for (size_t j = 0; j < triList.size(); j++) {
				if (triList[j].ifSameTri(t))
					std::swap(triList[j], newTri[0]);
				if(triList[j].ifSameTri(next))
					std::swap(triList[j], newTri[1]);
			}
	}
}
