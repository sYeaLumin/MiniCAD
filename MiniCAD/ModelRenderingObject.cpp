#include "ModelRenderingObject.h"



ModelRenderingObject::ModelRenderingObject()
{
}


ModelRenderingObject::~ModelRenderingObject()
{
}

void ModelRenderingObject::init()
{
	initializeOpenGLFunctions();
}

void ModelRenderingObject::draw(LShaderProgram & shaderPorgram, GLenum mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	shaderPorgram.bind();
	shaderPorgram.setUniform();

	m_vao.bind();

	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	m_vao.release();

	shaderPorgram.release();

	glDisable(GL_MULTISAMPLE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEBUG_OUTPUT);
}

void ModelRenderingObject::createRenderBuffers()
{
	createVAOABO(m_vertices, m_normals);
}

void ModelRenderingObject::updateRenderBuffers()
{
	rewriteVBO(m_vertices, m_normals);
}
