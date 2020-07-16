#pragma once
#include <GL/glew.h>
#include "../globalVar.h"

class VertexBuffer{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const float* data, const unsigned int& size);
	explicit VertexBuffer(const Vertex* data, const unsigned int& size);
	~VertexBuffer() { Release(); }

	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept
		: m_RendererID(other.m_RendererID)
	{
		other.m_RendererID = 0;
	}

	VertexBuffer& operator=(VertexBuffer&& other) noexcept{
		if (this != &other) {
			Release();
			m_RendererID = other.m_RendererID;
			other.m_RendererID = 0;
		}
		return *this;
	}

	void Release() {
		if (m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void Bind() const;
	void Unbind() const;
};