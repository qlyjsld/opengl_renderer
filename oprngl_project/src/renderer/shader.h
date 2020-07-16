#pragma once
#include <string>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSources {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_Filepath;
	ShaderProgramSources sources;
	//caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader() {
		Release();
	}
	Shader(const Shader& shader) = delete;
	Shader& operator=(const Shader& shader) = delete;
	
	Shader(Shader&& other) noexcept
		: m_Filepath(other.m_Filepath), shaderID(other.shaderID), m_UniformLocationCache(other.m_UniformLocationCache)
	{
		other.shaderID = 0;
	}

	Shader& operator=(Shader&& other) noexcept{
		if (this != &other) {
			Release();
			m_Filepath = other.m_Filepath;
			shaderID = other.shaderID;
			m_UniformLocationCache = other.m_UniformLocationCache;
			other.shaderID = 0;
		}
		return *this;
	}

	void Release() {
		if (shaderID)
			glDeleteProgram(shaderID);
	}

	void Bind() const;
	void Unbind() const;
	unsigned int shaderID;
	int GetUniformLocation(const std::string& name);
	
	template <typename T>
	void updateUniform(const std::string& name, const T& num) {
		static_assert(false);
	}

	template<>
	void updateUniform<glm::vec3>(const std::string& name, const glm::vec3& num) {
		Bind();
		glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(num));
		Unbind();
	}

	template<>
	void updateUniform<float>(const std::string& name, const float& num) {
		Bind();
		glUniform1f(GetUniformLocation(name), num);
		Unbind();
	}

	template<>
	void updateUniform<glm::mat4>(const std::string& name, const glm::mat4& num) {
		Bind();
		glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(num));
		Unbind();
	}

	template<>
	void updateUniform<int>(const std::string& name, const int& num) {
		Bind();
		glUniform1i(GetUniformLocation(name), num);
		Unbind();
	}

private:
	void CompileShader();
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int ComplierShader(const unsigned int& type, const std::string& source);
	ShaderProgramSources ParseShader(const std::string& filepath);
};
