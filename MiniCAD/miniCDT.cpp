#include "miniCDT.h"
#define MIN 1e-6
void CAD::miniCDT::init(shared_ptr<Face>& face)
{
	if (ifLog)
		qDebug() << "FUNC init : ";
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
	if(ifLog)
		qDebug() << "		normal : " << normal.x << " : " << normal.y << " : " << normal.z;

	//投影到平面
	vList.clear();
	cCenter = glm::vec3(pList[0].pos[0], pList[0].pos[1], pList[0].pos[2]);
	cEye = cCenter + normal * float(tmp1.length());
	front = glm::normalize(cCenter - cEye);
	glm::vec3 worldUp = glm::vec3(tmp1.pos[0], tmp1.pos[1], tmp1.pos[2]);
	right = glm::normalize(glm::cross(front, worldUp));
	cUp = glm::normalize(glm::cross(right, front));
	viewMat = glm::lookAt(cEye, cCenter, cUp);
	for (size_t i = 0; i < pList.size(); i++) {
		glm::vec4 oldP = glm::vec4(pList[i].pos[0], pList[i].pos[1], pList[i].pos[2], 1.0f);
		glm::vec2 newP = viewMat * oldP; //舍弃z轴量
		vList.push_back(newP);
		if (ifLog)
			qDebug() << "		v" << i << " oldP : " << oldP.x << " , " << oldP.y << " , " << oldP.z << " newP : " << newP.x << " , " << newP.y;
	}
}

void CAD::miniCDT::Triangulate()
{
	if (ifLog)
		qDebug() << "FUNC Triangulate : ";

	float MAX = 1000.0;
	int top, left, right;
	int size = pList.size();
	bool* ifUsed = new bool[size];
	for (size_t i = 0; i < pList.size(); i++) ifUsed[i] = false;
	triList.clear();

	top = vList.size();
	vList.push_back(glm::vec2(0.5f, MAX));
	left = vList.size();
	vList.push_back(glm::vec2(-MAX, -MAX));
	right = vList.size();
	vList.push_back(glm::vec2(MAX, -MAX));
	triList.push_back(make_shared<Tri>(top, left, right));

	uniform_int_distribution<int> Rand(0, size);
	for (size_t i = 0; i < size; i++) {
		int index = 0;
		int r = Rand(randE) % (size - i);

		// 随机找下一个要加入的点
		for (size_t j = 0, k = 0; j < size; j++) {
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
		if (ifLog)
			qDebug() << "		index = " <<  index;

		//落在边上
		bool flag = true;
		for (size_t j = 0; j < triList.size() && flag; j++) {
			for (size_t k = 0; k < 3; k++) {
				if (ifOnEdge(vList[triList[j]->v[k]], vList[triList[j]->v[(k + 1) % 3]], vList[index])) {
					addOnEdge(triList[j], k, index);
					flag = false;
					break;
				}
			}
		}
		if (ifLog) {
			if(flag)
				qDebug() << "		InTriangle !";
			else
				qDebug() << "		OnEdge !";
		}

		//落在三角形内
		if (flag)
			for (size_t j = 0; j < triList.size(); j++) {
				if (ifInTriangle(vList[triList[j]->v[0]], vList[triList[j]->v[1]], vList[triList[j]->v[2]], vList[index])) {
					addInTri(triList[j], index);
					break;
				}
			}

		if (ifLog)
			Log();
	}
	//删除超三角
	vector<shared_ptr<Tri>>::iterator currT;
	for (currT = triList.begin(); currT != triList.end();)
	{
		if ((*currT)->v[0] >= pList.size() ||
			(*currT)->v[1] >= pList.size() ||
			(*currT)->v[2] >= pList.size()) {
			removeTri((*currT));
			currT = triList.erase(currT); // 删除并指向下一个
		}
		else
			++currT;
	}
	if (ifLog)
		Log();
}

void CAD::miniCDT::Log()
{
	qDebug() << "		FUNC Log : ";
	for (size_t i = 0; i < triList.size(); i++) {
		shared_ptr<Tri> currTri = triList[i];
		if (ifLog)
			qDebug() << "			tri : " << currTri->v[0] << " , " << currTri->v[1] << " , " << currTri->v[2];
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

void CAD::miniCDT::setUpLineDataTest2(vector<Point>& vertexData)
{
	if (ifLog)
		qDebug() << "FUNC setUpLineDataTest2 : ";
	Point offset(normal.x, normal.y, normal.z);
	double off = 0.2;
	for (size_t i = 0; i < triList.size(); i++) {
		shared_ptr<Tri> currTri = triList[i];
		if (ifLog)
			qDebug() << "		tri : " << currTri->v[0] << " , " << currTri->v[1] << " , " << currTri->v[2];
		for (size_t j = 0; j < 3; j++) {
			Point newStartP = pList[currTri->v[j]] + offset * off;
			Point newEndP = pList[currTri->v[(j + 1) % 3]] + offset * off;
			vertexData.push_back(newStartP);
			vertexData.push_back(newEndP);
		}
	}
}

bool CAD::miniCDT::ifOnEdge(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p)
{
	float dis, dis1, dis2;
	dis = glm::distance(p1, p2);
	dis1 = glm::distance(p, p1);
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

void CAD::miniCDT::addOnEdge(shared_ptr<Tri> t, int e, int v)
{
	int p, a, b, d = 0;
	shared_ptr<Tri> bp, pa, ad, db, next;

	next = t->adjTri[e].lock();
	bp = t->adjTri[(e + 1) % 3].lock();
	pa = t->adjTri[(e + 2) % 3].lock();

	a = t->v[e];
	b = t->v[(e + 1) % 3];
	p = t->v[(e + 2) % 3];

	if (next == nullptr) {
		//Tri newTri[2];
		shared_ptr<Tri> newTri[2];
		newTri[0] = make_shared<Tri>(p, a, v);
		newTri[1] = make_shared<Tri>(p, v, b);

		newTri[0]->adjTri[0] = pa;
		newTri[0]->adjTri[2] = newTri[1];//写法？
		if (pa != nullptr)
			pa->changeAdj(t, newTri[0]);

		newTri[1]->adjTri[0] = newTri[0];
		newTri[1]->adjTri[2] = bp;
		if (bp != nullptr)
			bp->changeAdj(t, newTri[1]);

		size_t f;
		for (f = 0; f < triList.size(); f++)
			if (triList[f]->ifSameTri(t))
				break;
		triList.erase(triList.begin() + f);
		for (size_t i = 0; i < 2; i++)
			triList.push_back(newTri[i]);
	}
	else {
		for (size_t i = 0; i < 3; i++) 
			if (next->v[i] != a && next->v[i] != b) {
				d = next->v[i];
				db = next->adjTri[i].lock();
				ad = next->adjTri[(i + 2) % 3].lock();
			}
		shared_ptr<Tri> newTri[4];
		newTri[0] = make_shared<Tri>(p, a, v);
		newTri[1] = make_shared<Tri>(p, v, b);
		newTri[2] = make_shared<Tri>(v, a, d);
		newTri[3] = make_shared<Tri>(v, d, b);

		newTri[0]->adjTri[0] = pa;
		newTri[0]->adjTri[1] = newTri[2];
		newTri[0]->adjTri[2] = newTri[1];
		if (pa != nullptr)
			pa->changeAdj(t, newTri[0]);

		newTri[1]->adjTri[0] = newTri[0];
		newTri[1]->adjTri[1] = newTri[3];
		newTri[1]->adjTri[2] = bp;
		if (bp != nullptr)
			bp->changeAdj(t, newTri[1]);

		newTri[2]->adjTri[0] = newTri[0];
		newTri[2]->adjTri[1] = ad;
		newTri[2]->adjTri[2] = newTri[3];
		if (ad != nullptr)
			ad->changeAdj(next, newTri[2]);

		newTri[3]->adjTri[0] = newTri[2];
		newTri[3]->adjTri[1] = db;
		newTri[3]->adjTri[2] = newTri[1];
		if (db != nullptr)
			db->changeAdj(next, newTri[3]);

		for (size_t j = 0; j < triList.size(); j++) {
			if (triList[j]->ifSameTri(t))
				triList[j] = newTri[0];
			if (triList[j]->ifSameTri(next))
				triList[j] = newTri[1];
		}
		triList.push_back(newTri[2]);
		triList.push_back(newTri[3]);

		swapTest(newTri[0], 0);
		swapTest(newTri[1], 2);
		swapTest(newTri[2], 1);
		swapTest(newTri[3], 1);
	}
}

bool CAD::miniCDT::ifInTriangle(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p3, glm::vec2 & p)
{
	int temp = orientation(p1, p2, p);
	return (orientation(p2, p3, p) == temp && orientation(p3, p1, p) == temp);
}

void CAD::miniCDT::addInTri(shared_ptr<Tri>& t, int v)
{
	shared_ptr<Tri> newTri[3];
	newTri[0] = make_shared<Tri>(t->v[0], t->v[1], v);
	newTri[1] = make_shared<Tri>(t->v[1], t->v[2], v);
	newTri[2] = make_shared<Tri>(t->v[2], t->v[0], v);

	newTri[0]->adjTri[0] = t->adjTri[0];
	newTri[0]->adjTri[1] = newTri[1];
	newTri[0]->adjTri[2] = newTri[2];

	newTri[1]->adjTri[0] = t->adjTri[1];
	newTri[1]->adjTri[1] = newTri[2];
	newTri[1]->adjTri[2] = newTri[0];

	newTri[2]->adjTri[0] = t->adjTri[2];
	newTri[2]->adjTri[1] = newTri[0];
	newTri[2]->adjTri[2] = newTri[1];

	for (size_t i = 0; i<3; i++) {
		if (t->adjTri[i].lock() != nullptr) {
			for (size_t j = 0; j < 3; j++) {
				shared_ptr<Tri> tmp = t->adjTri[i].lock()->adjTri[j].lock();
				if (tmp && tmp->ifSameTri(t))
					t->adjTri[i].lock()->adjTri[j] = newTri[i];
			}
		}
	}

	for (size_t i = 0; i < triList.size(); i++)
		if (triList[i]->ifSameTri(t))
		{
			triList[i] = newTri[0];
			break;
		}
	triList.push_back(newTri[1]);
	triList.push_back(newTri[2]);

	swapTest(newTri[0], 0);
	swapTest(newTri[1], 0);
	swapTest(newTri[2], 0);
}

bool CAD::miniCDT::ifInCircle(Circle & c, glm::vec2 & p)
{
	return glm::length(c.c - p) < (c.r + MIN);
}

bool CAD::miniCDT::ifBEdge(int v1, int v2)
{
	if (v1 >= pList.size() || v2 >= pList.size()) return false;
	return (abs(v1 - v2) == 1 || abs(v1 - v2) == pList.size() - 1);
}

void CAD::miniCDT::swapTest(shared_ptr<Tri>& t, int e)
{
	if (ifLog) {
		qDebug() << "FUNC swapTest : ";
		qDebug() << "		t : " << t->v[0] << " , " << t->v[1] << " , " << t->v[2];
	}
	int p, a, b, d = 0;
	shared_ptr<Tri> bp, pa, ad, db, next;

	next = t->adjTri[e].lock();
	bp = t->adjTri[(e + 1) % 3].lock();
	pa = t->adjTri[(e + 2) % 3].lock();

	a = t->v[e];
	b = t->v[(e + 1) % 3];
	p = t->v[(e + 2) % 3];

	if (next != nullptr) {
		Circle c (vList[t->v[0]], vList[t->v[1]], vList[t->v[2]]);
		if (ifLog){
			qDebug() << "		Circle : " << t->v[0] << " , " << t->v[1] << " , " << t->v[2];
			qDebug() << "		Circle c : " << c.c.x << " , " << c.c.y;
			qDebug() << "		Circle r : " << c.r;
		}
		for (size_t i = 0; i < 3; i++)
			if (next->v[i] != a && next->v[i] != b) {
				d = next->v[i];
				db = next->adjTri[i].lock();
				ad = next->adjTri[(i + 2) % 3].lock();
			}

		if (ifLog)
			qDebug() << "		d : " << d;
		//if (ifInCircle(c, vList[d]) && !ifBEdge(a, b)) {
		if (ifInCircle(c, vList[d])) {
			if (ifLog)
				qDebug() << "		ifInCircle(c, vList[d])";
			shared_ptr<Tri> newTri[2];
			newTri[0] = make_shared<Tri>(p, d, b);
			newTri[1] = make_shared<Tri>(p, a, d);

			newTri[0]->adjTri[0] = newTri[1];
			newTri[0]->adjTri[1] = db;
			newTri[0]->adjTri[2] = bp;
			if (db != nullptr)
				db->changeAdj(next, newTri[0]);
			if (bp != nullptr)
				bp->changeAdj(t, newTri[0]);

			newTri[1]->adjTri[0] = pa;
			newTri[1]->adjTri[1] = ad;
			newTri[1]->adjTri[2] = newTri[0];
			if (pa != nullptr)
				pa->changeAdj(t, newTri[1]);
			if (ad != nullptr)
				ad->changeAdj(next, newTri[1]);

			for (size_t j = 0; j < triList.size(); j++) {
				if (triList[j]->ifSameTri(t))
					triList[j] = newTri[0];
				if (triList[j]->ifSameTri(next))
					triList[j] = newTri[1];
			}

			swapTest(newTri[0], 1);
			swapTest(newTri[1], 1);
		}
	}

}

void CAD::miniCDT::removeTri(shared_ptr<Tri>& t)
{
	for (size_t i = 0; i<3; i++)
		if (t->adjTri[i].lock() != nullptr)
			for (size_t j = 0; j < 3; j++) {
				shared_ptr<Tri> tmp = t->adjTri[i].lock()->adjTri[j].lock();
				if (tmp && tmp->ifSameTri(t))
					t->adjTri[i].lock()->adjTri[j].lock() = nullptr;
			}
}

int CAD::miniCDT::orientation(glm::vec2 & p1, glm::vec2 & p2, glm::vec2 & p3)
{
	float d = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y -
		p1.y * p2.x - p2.y * p3.x - p3.y * p1.x;

	return (d < -MIN) ? -1 : (d > MIN ? 1 : 0);
}
