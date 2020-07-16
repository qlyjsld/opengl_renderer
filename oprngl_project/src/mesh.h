#pragma once
#include "renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "globalVar.h"
#include "renderer/VertexBuffer.h"

#include <vector>

class mesh {
private:
	void setupMesh();
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	VertexBufferLayout layout;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Textures> textures;

	mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Textures>& textures)
		: va(), vb(&vertices[0], vertices.size() * sizeof(Vertex)), ib(&indices[0], indices.size()), layout()
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}


	void draw(Shader& shader);
};
