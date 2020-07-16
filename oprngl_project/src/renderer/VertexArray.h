#pragma once

#include "VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int vaID;
public:
	VertexArray();
	~VertexArray() { Release(); }

	VertexArray(const VertexArray& va) = delete;
	VertexArray& operator=(const VertexArray& va) = delete;

	VertexArray(VertexArray&& other) noexcept
		: vaID(other.vaID)
	{
		other.vaID = 0;
	}

	VertexArray& operator=(VertexArray&& other) noexcept{
		if (this != &other) {
			Release();
			vaID = other.vaID;
			other.vaID = 0;
		}
		return *this;
	}

	void Release() {
		if (vaID)
			glDeleteVertexArrays(1, &vaID);
	}

	void AddBuffer(const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};