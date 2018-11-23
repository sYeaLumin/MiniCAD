#include "Modeler.h"


Modeler::Modeler()
{
}


Modeler::~Modeler()
{
}

void Modeler::draw(LShaderProgram & shader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_MULTISAMPLE);

	shader.bind();
	shader.setUniform();

	//»æÖÆ¿ªÊ¼
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

	//»æÖÆ½áÊø

	shader.release();

	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEBUG_OUTPUT);
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
	//µ×±ß
	shared_ptr<Solid> currSolid = eulerOP.mvfs(subface[0]);
	if (!addNewSolid(currSolid)) {
		cout << "Modeler::testModelCube : mvfs failed !" << endl;
		return;
	}
	shared_ptr<HalfEdge> currHalfEdge;
	currHalfEdge = eulerOP.mev(subface[0], subface[1], currSolid->sFaces->fLoops);//Loop£¿
	currHalfEdge = eulerOP.mev(subface[1], subface[2], currHalfEdge->heLoop.lock());
	currHalfEdge = eulerOP.mev(subface[2], subface[3], currHalfEdge->heLoop.lock());
	shared_ptr<Loop> currLoop;
	currLoop = eulerOP.mef(subface[3], subface[0], currHalfEdge->heLoop.lock());
	//²à±ß
	eulerOP.mev(subface[0], topface[0], currLoop);
	eulerOP.mev(subface[1], topface[1], currLoop);
	eulerOP.mev(subface[2], topface[2], currLoop);
	eulerOP.mev(subface[3], topface[3], currLoop);
	//¶¥±ß
	eulerOP.mef(topface[0], topface[1], currLoop);
	eulerOP.mef(topface[1], topface[2], currLoop);
	eulerOP.mef(topface[2], topface[3], currLoop);
	eulerOP.mef(topface[3], topface[0], currLoop);
}
