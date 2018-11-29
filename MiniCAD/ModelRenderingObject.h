#pragma once
#include "LOpenGL\LRenderingObject.h"
class ModelRenderingObject :
	public LRenderingObject
{
public:
	ModelRenderingObject();
	~ModelRenderingObject();

	virtual void init() override;
	virtual void draw(LShaderProgram &shaderPorgram, GLenum mode = GL_TRIANGLES) override;
	virtual void createRenderBuffers() override;
	virtual void updateRenderBuffers() override;

public:
	void addV(glm::vec3 & v) { m_vertices.push_back(v); }
	void addN(glm::vec3 & n) { m_normals.push_back(n); }
	void clearData() {
		m_vertices.clear();
		m_normals.clear();
	}

};

