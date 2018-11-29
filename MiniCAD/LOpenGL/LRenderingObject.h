#ifndef MY_RENDERING_OBJECT_H
#define MY_RENDERING_OBJECT_H

#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <glm.hpp>
#include "LShaderProgram.h"

class LRenderingObject : public QOpenGLFunctions
{
public:
	LRenderingObject();
	~LRenderingObject();

	// get functions
	const std::vector<glm::vec3> &getVertices() const;
	const std::vector<glm::vec3> &getNormals() const;

	//////////////////////////////////////////////////////////////////////////
	// opengl render functions
public:
	virtual void init() = 0;
	virtual void draw(LShaderProgram &shaderPorgram, GLenum mode=GL_TRIANGLES) = 0;
	virtual void createRenderBuffers() = 0;
	virtual void updateRenderBuffers() = 0;

protected:
	virtual void createVAOABO(const std::vector<glm::vec3> &vertices);
	virtual void createVAOABO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals);
	virtual void createVAOABO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals, const std::vector<glm::vec3> &colors);

	virtual void rewriteVBO(const std::vector<glm::vec3> &vertices);
	virtual void rewriteVBO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals);
	virtual void rewriteVBO(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals, const std::vector<glm::vec3> &colors);

protected:
	// geometry data
	unsigned int m_numVertex;
	unsigned int m_numTriangle;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_normals;

	// opengl render data
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
};

#endif