#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "mesh.h"
#include "renderer/shader.h"
#include "assimp/scene.h"
#include <string>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory);

class model {
private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Textures> loadMaterialTextures(aiMaterial* mat, const aiTextureType& type, const std::string& typeName);
public:
	std::vector<Textures> textures_loaded;
	std::vector<mesh*> meshes;
	std::string directory;

	model(const std::string& path) {
		loadModel(path);
	}
	
	~model() {
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			delete meshes[i];
		}
	}
	
	void draw(Shader& shader) {
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->draw(shader);
		}
	}
};