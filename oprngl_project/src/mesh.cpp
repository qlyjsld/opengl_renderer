#include "pch.h"
#include "mesh.h"

void mesh::setupMesh() {
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(layout);
}

void mesh::draw(Shader& shader) {
	unsigned int diffuseNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
		number = std::to_string(diffuseNr++);
		shader.updateUniform<int>((name + number).c_str(), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	Renderer render;
	render.Draw(va, ib, shader);
}