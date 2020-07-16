#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shader.h"

#ifdef _DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

#define len(x) sizeof(x)/sizeof(x[0])
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawSquare(const VertexArray& va, const Shader& shader) const;
	void Clear() const;
};