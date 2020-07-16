#include "../pch.h"
#include "Renderer.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &vaID));
	Bind();
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout) {
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * sizeof(element.type);
	}
	
}

void VertexArray::Bind() const{
	GLCall(glBindVertexArray(vaID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}