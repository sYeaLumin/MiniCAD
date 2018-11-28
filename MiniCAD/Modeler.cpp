#include "Modeler.h"
#include "LOpenGL\LgluTess.h"

Modeler::Modeler()
{
}


Modeler::~Modeler()
{
}

void Modeler::init()
{
	initializeOpenGLFunctions();
}

void Modeler::draw(LShaderProgram & shader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);

	shader.bind();
	shader.setUniform();

	//绘制开始
	GLUtesselator* tessobj = gluNewTess();

	if (!tessobj) return;

	gluTessCallback(tessobj, GLU_TESS_VERTEX, (void (CALLBACK *)())vertexCallback);
	gluTessCallback(tessobj, GLU_TESS_BEGIN, (void (CALLBACK *)())beginCallback);
	gluTessCallback(tessobj, GLU_TESS_END, (void (CALLBACK *)())endCallback);
	gluTessCallback(tessobj, GLU_TESS_ERROR, (void (CALLBACK *)())errorCallback);
	gluTessCallback(tessobj, GLU_TESS_COMBINE, (void (CALLBACK *)())combineCallback);

	for (int i = 0; i < faceData.size(); i++)
	{
		vector<vector<Point>> oneFaceData = faceData[i];

		gluTessBeginPolygon(tessobj, NULL);

		// outloope
		gluTessBeginContour(tessobj);

		vector<Point> outLoopData = oneFaceData[0];
		for (int j = 0; j < outLoopData.size(); j++)
		{
			gluTessVertex(tessobj, outLoopData[j].pos, outLoopData[j].pos);
			
		}
		gluTessEndContour(tessobj);

		// inner loop
		vector<Point> innerLoopData;
		for (int j = 1; j < oneFaceData.size(); j++)
		{
			gluTessBeginContour(tessobj);
			innerLoopData = oneFaceData[j];
			for (int k = 0; k < innerLoopData.size(); k++)
			{
				gluTessVertex(tessobj, innerLoopData[k].pos, innerLoopData[k].pos);
			}
			gluTessEndContour(tessobj);
		}

		gluTessEndPolygon(tessobj);
	}
	gluDeleteTess(tessobj);

	//绘制结束

	shader.release();

	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEBUG_OUTPUT);
}

void Modeler::drawLine(LShaderProgram & shader)
{
	//modeler.setupLineData();
	glLineWidth(4);
	glShadeModel(GL_SMOOTH);
	// shader use
	shader.bind();
	shader.setUniform();

	glBegin(GL_LINES);
	for (int i = 0; i < vertexData.size(); i++)
	{
		Point onePoint = vertexData[i];
		glVertex3f(onePoint.pos[0], onePoint.pos[1], onePoint.pos[2]);
	}
	glEnd();
}

void Modeler::setupLineData()
{
	vertexData.clear();
	shared_ptr<Solid> currSolid;
	shared_ptr<Edge> currEdge;
	shared_ptr<HalfEdge> currHEdge;
	shared_ptr<Face> currFace;
	shared_ptr<Loop> currLoop;

	currSolid = solidList;
	for (currSolid; currSolid != nullptr; currSolid = currSolid->next)
	{
		for (currEdge = currSolid->sEdges; currEdge != nullptr; currEdge = currEdge->next) {
			Point startVert = currEdge->leftHE->startVertex->p;
			Point endVert = currEdge->rightHE->startVertex->p;
			Point midVert = (startVert + endVert) * 0.5;
			vertexData.push_back(startVert);
			vertexData.push_back(endVert);
		}
	}
}

void Modeler::setupLineDataTest1()
{
	vertexData.clear();
	shared_ptr<Solid> currSolid;
	shared_ptr<Edge> currEdge;
	shared_ptr<HalfEdge> currHEdge;
	shared_ptr<Face> currFace;
	shared_ptr<Loop> currLoop;

	currSolid = solidList;
	for (currSolid; currSolid != nullptr; currSolid = currSolid->next)
	{
		for (currFace = currSolid->sFaces; currFace != nullptr; currFace = currFace->next)
		{
			qDebug() << "	currFace ID : " << currFace->fID;
			for (currLoop = currFace->fLoops; currLoop != nullptr; currLoop = currLoop->next)
			{
				currHEdge = currLoop->lHalfEdges;
				Point startVert = currHEdge->startVertex->p;
				Point endVert = currHEdge->next->startVertex->p;
				Point nextVert = currHEdge->next->next->startVertex->p;
				Point offset1 = (endVert - startVert) * 0.4;
				Point offset2 = (nextVert - endVert) * 0.2;
				vertexData.push_back(startVert);
				vertexData.push_back(Point(startVert + offset1 + offset2));
				//vertexData.push_back(startVert);
				//vertexData.push_back(endVert);
				qDebug() << "		currLoop ID : " << currLoop->lID;
				qDebug() << "			currHEdge ID : " << currHEdge->heID;
				qDebug() << "				startVert ID : " << currHEdge->startVertex->vID;
				qDebug() << "				endVert ID : " << currHEdge->next->startVertex->vID;
				/**/
				for (currHEdge = currHEdge->next; currHEdge != currLoop->lHalfEdges; currHEdge = currHEdge->next)
				{
					//Point startVert = currHEdge->startVertex->p;
					//Point endVert = currHEdge->next->startVertex->p;
					//vertexData.push_back(startVert);
					//vertexData.push_back(endVert);
					Point startVert = currHEdge->startVertex->p;
					Point endVert = currHEdge->next->startVertex->p;
					Point nextVert = currHEdge->next->next->startVertex->p;
					Point offset1 = (endVert - startVert) * 0.5;
					Point offset2 = (nextVert - endVert) * 0.1;
					vertexData.push_back(startVert);
					vertexData.push_back(Point(startVert + offset1 + offset2));
					qDebug() << "			currHEdge ID : " << currHEdge->heID;
					qDebug() << "				startVert ID : " << currHEdge->startVertex->vID;
					qDebug() << "				endVert ID : " << currHEdge->next->startVertex->vID;
				}
			}
		}
	}
}

void Modeler::setupLineDataTest2()
{
	vertexData.clear();
	shared_ptr<Solid> currSolid;
	shared_ptr<Edge> currEdge;
	shared_ptr<HalfEdge> currHEdge;
	shared_ptr<Face> currFace;
	shared_ptr<Loop> currLoop;
	double off = 0.2;
	currSolid = solidList;
	for (currSolid; currSolid != nullptr; currSolid = currSolid->next)
	{
		for (currFace = currSolid->sFaces; currFace != nullptr; currFace = currFace->next)
		{
			qDebug() << "	currFace ID : " << currFace->fID;
			for (currLoop = currFace->fLoops; currLoop != nullptr; currLoop = currLoop->next)
			{
				qDebug() << "		currLoop ID : " << currLoop->lID;
				currHEdge = currLoop->lHalfEdges;
				Point pList[3];
				pList[0] = currHEdge->startVertex->p;
				pList[1] = currHEdge->next->startVertex->p;
				pList[2] = currHEdge->next->next->startVertex->p;
				Point tmp1 = pList[1] - pList[0];
				Point tmp2 = pList[2] - pList[1];
				glm::vec3 normal = glm::normalize(glm::cross(
					glm::vec3(tmp2.pos[0], tmp2.pos[1], tmp2.pos[2]),
					glm::vec3(tmp1.pos[0], tmp1.pos[1], tmp1.pos[2])
				));
				qDebug() << "		normal : " << normal.x << " : " << normal.y << " : " << normal.z;
				Point offset(normal.x, normal.y, normal.z);
				Point startVert = currHEdge->startVertex->p;
				Point endVert = currHEdge->next->startVertex->p;
				Point newStartVert = startVert + offset * off;
				Point newEndVert = endVert + offset * off;
				vertexData.push_back(newStartVert);
				vertexData.push_back(newEndVert);

				for (currHEdge = currHEdge->next; currHEdge != currLoop->lHalfEdges; currHEdge = currHEdge->next)
				{
					Point startVert2 = currHEdge->startVertex->p;
					Point endVert2 = currHEdge->next->startVertex->p;
					Point newStartVert2 = startVert2 + offset * off;
					Point newEndVert2 = endVert2 + offset * off;
					vertexData.push_back(newStartVert2);
					vertexData.push_back(newEndVert2);
				}
			}
		}
	}
}

void Modeler::setupLineDataTestCDT1()
{
	vertexData.clear();
	shared_ptr<Solid> currSolid;
	shared_ptr<Face> currFace;
	double off = 0.2;
	currSolid = solidList;
	miniCDT cdt;
	for (currSolid; currSolid != nullptr; currSolid = currSolid->next)
	{
		for (currFace = currSolid->sFaces; currFace != nullptr; currFace = currFace->next)
		{
			cdt.init(currFace);
			cdt.setUpLineDataTest1(vertexData);
		}
	}

}

bool Modeler::addNewSolid(shared_ptr<Solid>& s)
{
	if (s == nullptr)
		return false;
	if (solidList == nullptr)
		solidList = s;
	else {
		shared_ptr<Solid> tmp = solidList;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = s;
	}
	return true;
}

void Modeler::testModelCube()
{
	Point subface[4] = {
		Point(0.5, 0.5, -0.5),
		Point(-0.5, 0.5, -0.5),
		Point(-0.5, -0.5, -0.5),
		Point(0.5, -0.5, -0.5)
	};
	Point topface[4] = {
		Point(0.5, 0.5, 0.5),
		Point(-0.5, 0.5, 0.5),
		Point(-0.5, -0.5, 0.5),
		Point(0.5, -0.5, 0.5)
	};
	//底边
	shared_ptr<Solid> currSolid = eulerOP.mvfs(subface[0]);
	if (!addNewSolid(currSolid)) {
		cout << "Modeler::testModelCube : mvfs failed !" << endl;
		return;
	}
	shared_ptr<HalfEdge> currHalfEdge;
	currHalfEdge = eulerOP.mev(subface[0], subface[1], currSolid->sFaces->fLoops);//Loop？
	currHalfEdge = eulerOP.mev(subface[1], subface[2], currHalfEdge->heLoop.lock());
	currHalfEdge = eulerOP.mev(subface[2], subface[3], currHalfEdge->heLoop.lock());
	shared_ptr<Loop> currLoop;
	currLoop = eulerOP.mef(subface[3], subface[0], currHalfEdge->heLoop.lock());
	/**/
	//侧边
	eulerOP.mev(subface[0], topface[0], currLoop);
	eulerOP.mev(subface[1], topface[1], currLoop);
	eulerOP.mev(subface[2], topface[2], currLoop);
	eulerOP.mev(subface[3], topface[3], currLoop);
	//顶边
	eulerOP.mef(topface[0], topface[1], currLoop);
	eulerOP.mef(topface[1], topface[2], currLoop);
	eulerOP.mef(topface[2], topface[3], currLoop);
	eulerOP.mef(topface[3], topface[0], currLoop);
}

void Modeler::testModelCube2()
{
	Point subface[4] = {
		Point(0.5, 0.5, -0.5),
		Point(-0.5, 0.5, -0.5),
		Point(-0.5, -0.5, -0.5),
		Point(0.5, -0.5, -0.5)
	};
	vector<shared_ptr<Loop>> sweepLoopList;
	//底边
	shared_ptr<Solid> currSolid = eulerOP.mvfs(subface[0]);
	if (!addNewSolid(currSolid)) {
		cout << "Modeler::testModelCube : mvfs failed !" << endl;
		return;
	}
	shared_ptr<HalfEdge> currHalfEdge;
	currHalfEdge = eulerOP.mev(subface[0], subface[1], currSolid->sFaces->fLoops);//Loop？
	currHalfEdge = eulerOP.mev(subface[1], subface[2], currHalfEdge->heLoop.lock());
	currHalfEdge = eulerOP.mev(subface[2], subface[3], currHalfEdge->heLoop.lock());
	shared_ptr<Loop> currLoop;
	currLoop = eulerOP.mef(subface[3], subface[0], currHalfEdge->heLoop.lock());
	sweepLoopList.push_back(currLoop);
	eulerOP.sweep(sweepLoopList, Point(0, 0, 1.0), 2.0);
}

void Modeler::testModelCubeWithHole()
{
	Point subface[4] = {
		Point(0.5, 0.5, -0.5),
		Point(-0.5, 0.5, -0.5),
		Point(-0.5, -0.5, -0.5),
		Point(0.5, -0.5, -0.5)
	};
	Point subHole[4] = {
		Point(0.25, 0.25, -0.5),
		Point(-0.25, 0.25, -0.5),
		Point(-0.25, -0.25, -0.5),
		Point(0.25, -0.25, -0.5)
	};
	//底边
	shared_ptr<Solid> currSolid = eulerOP.mvfs(subface[0]);
	if (!addNewSolid(currSolid)) {
		cout << "Modeler::testModelCube : mvfs failed !" << endl;
		return;
	}
	shared_ptr<HalfEdge> currHalfEdge;
	currHalfEdge = eulerOP.mev(subface[0], subface[1], currSolid->sFaces->fLoops);//Loop？
	currHalfEdge = eulerOP.mev(subface[1], subface[2], currHalfEdge->heLoop.lock());
	currHalfEdge = eulerOP.mev(subface[2], subface[3], currHalfEdge->heLoop.lock());
	shared_ptr<Loop> sweepLoop;
	sweepLoop = eulerOP.mef(subface[3], subface[0], currHalfEdge->heLoop.lock());

	eulerOP.mev(subface[0], subHole[0], currSolid->sFaces->fLoops);
	shared_ptr<Loop> inLoop;
	inLoop = eulerOP.kemr(subface[0], subHole[0], currSolid->sFaces->fLoops);
	eulerOP.mev(subHole[0], subHole[1], inLoop);
	eulerOP.mev(subHole[1], subHole[2], inLoop);
	eulerOP.mev(subHole[2], subHole[3], inLoop);
	shared_ptr<Loop> sweepInLoop;
	sweepInLoop = eulerOP.mef(subHole[3], subHole[0], inLoop);

	sweepLoop->next = sweepInLoop;
	eulerOP.sweep(sweepLoop->lFace.lock(), Point(0, 0, 1.0), 2.0);
	//eulerOP.sweep(currSolid->sFaces, Point(0, 0, 1.0), 2.0);//与mvf中新环的选择有关

	qDebug() << "Finish !";
}

void Modeler::testModelCubeWithHole2()
{
	Point subface[4] = {
		Point(0.5, 0.5, -0.5),
		Point(-0.5, 0.5, -0.5),
		Point(-0.5, -0.5, -0.5),
		Point(0.5, -0.5, -0.5)
	};
	Point subHole[4] = {
		Point(0.25, 0.25, -0.5),
		Point(-0.25, 0.25, -0.5),
		Point(-0.25, -0.25, -0.5),
		Point(0.25, -0.25, -0.5)
	};
	vector<shared_ptr<Loop>> sweepLoopList;
	//底边
	shared_ptr<Solid> currSolid = eulerOP.mvfs(subface[0]);
	if (!addNewSolid(currSolid)) {
		cout << "Modeler::testModelCube : mvfs failed !" << endl;
		return;
	}
	shared_ptr<HalfEdge> currHalfEdge;
	currHalfEdge = eulerOP.mev(subface[0], subface[1], currSolid->sFaces->fLoops);//Loop？
	currHalfEdge = eulerOP.mev(subface[1], subface[2], currHalfEdge->heLoop.lock());
	currHalfEdge = eulerOP.mev(subface[2], subface[3], currHalfEdge->heLoop.lock());

	sweepLoopList.push_back(eulerOP.mef(subface[3], subface[0], currHalfEdge->heLoop.lock()));

	eulerOP.mev(subface[0], subHole[0], currSolid->sFaces->fLoops);
	shared_ptr<Loop> inLoop;
	inLoop = eulerOP.kemr(subface[0], subHole[0], currSolid->sFaces->fLoops);
	eulerOP.mev(subHole[0], subHole[1], inLoop);
	eulerOP.mev(subHole[1], subHole[2], inLoop);
	eulerOP.mev(subHole[2], subHole[3], inLoop);
	shared_ptr<Loop> inLoop2 = eulerOP.mef(subHole[3], subHole[0], inLoop);
	//sweepLoopList.push_back(inLoop2);
	swapUpLinkForLoop(inLoop, inLoop2);
	sweepLoopList.push_back(inLoop);
	eulerOP.sweep(sweepLoopList, Point(0, 0, 1.0), 2.0);

	qDebug() << "Finish !";
}
