#include "LRenderingObject.h"

LRenderingObject::LRenderingObject()
	: QOpenGLFunctions(), 
	m_numVertex(0), m_numTriangle(0),
	m_vbo(QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
{

}

LRenderingObject::~LRenderingObject()
{
}

//////////////////////////////////////////////////////////////////////////
// geometry operation functions

const std::vector<glm::vec3> & LRenderingObject::getVertices() const
{
	return m_vertices;
}

const std::vector<glm::vec3> & LRenderingObject::getNormals() const
{
	return m_normals;
}


//////////////////////////////////////////////////////////////////////////
// opengl render function

//void LRenderingObject::draw(QOpenGLShaderProgram &shaderPorgram, GLenum mode)
//{
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//	glEnable(GL_DEBUG_OUTPUT);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_MULTISAMPLE);
//
//	shaderPorgram.bind();
//
//	m_vao.bind();
//	m_ebo.bind();
//	glDrawElements(mode, m_drawCount, GL_UNSIGNED_INT, 0);
//	m_ebo.release();
//	m_vao.release();
//
//	shaderPorgram.release();
//
//	glDisable(GL_MULTISAMPLE);
//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_DEBUG_OUTPUT);
//}

void LRenderingObject::createVAOABO(const std::vector<glm::vec3> &vertices)
{
	if (m_vao.isCreated())
	{
		return;
	}
	m_vao.create();
	m_vbo.create();

	size_t n = vertices.size();

	m_vao.bind();
	m_vbo.bind();

	m_vbo.allocate(n * sizeof(glm::vec3));
	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	m_vbo.release();
	m_vao.release();
}

void LRenderingObject::createVAOABO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &colors)
{
	if (m_vao.isCreated())
	{
		return;
	}
	m_vao.create();
	m_vbo.create();

	size_t n = vertices.size();

	m_vao.bind();
	m_vbo.bind();

	m_vbo.allocate(2 * n * sizeof(glm::vec3));
	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	m_vbo.write(n * sizeof(glm::vec3), colors.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(n * sizeof(glm::vec3)));

	m_vbo.release();
	m_vao.release();
}

void LRenderingObject::createVAOABO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals, const std::vector<glm::vec3> &colors)
{
	if (m_vao.isCreated())
	{
		return;
	}
	m_vao.create();
	m_vbo.create();

	size_t n = vertices.size();

	m_vao.bind();
	m_vbo.bind();

	m_vbo.allocate(3 * n * sizeof(glm::vec3));

	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	m_vbo.write(n * sizeof(glm::vec3), normals.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(n * sizeof(glm::vec3)));

	m_vbo.write(2 * n * sizeof(glm::vec3), colors.data(), n * sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(2 * n * sizeof(glm::vec3)));

	m_vbo.release();
	m_vao.release();
}

void LRenderingObject::rewriteVBO(const std::vector<glm::vec3> &vertices)
{
	size_t n = vertices.size();
	m_vbo.bind();
	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	m_vbo.release();
}

void LRenderingObject::rewriteVBO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals)
{
	size_t n = vertices.size();
	m_vbo.bind();
	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	m_vbo.write(n * sizeof(glm::vec3), normals.data(), n * sizeof(glm::vec3));
	m_vbo.release();
}

void LRenderingObject::rewriteVBO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals, const std::vector<glm::vec3> &colors)
{
	size_t n = vertices.size();
	m_vbo.bind();
	m_vbo.write(0, vertices.data(), n * sizeof(glm::vec3));
	m_vbo.write(n * sizeof(glm::vec3), normals.data(), n * sizeof(glm::vec3));
	m_vbo.write(2 * n * sizeof(glm::vec3), colors.data(), n * sizeof(glm::vec3));
	m_vbo.release();
}