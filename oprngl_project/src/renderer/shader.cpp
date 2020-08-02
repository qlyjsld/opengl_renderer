#include "pch.h"
#include "Renderer.h"

Shader::Shader(const std::string& filepath)
	: m_Filepath(filepath), shaderID(0)
{
	CompileShader();
    Bind();
}

void Shader::Bind() const{
    GLCall(glUseProgram(shaderID));
}

void Shader::Unbind() const{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    int location = glGetUniformLocation(shaderID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform " << name << " doesn't exist!" << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::CompileShader() {
    sources = Shader::ParseShader(m_Filepath);
    shaderID = CreateShader(sources.VertexSource, sources.FragmentSource);
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    GLCall(unsigned int vs = ComplierShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = ComplierShader(GL_FRAGMENT_SHADER, fragmentShader));
    GLCall(glAttachObjectARB(program, vs));
    GLCall(glAttachObjectARB(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::ComplierShader(const unsigned int& type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    GLCall(const char* src = source.c_str());
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    GLCall(if (!result) {
        int length = 1024;
        char message[1024];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader " : "Fragment Shader ") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    });

    return id;
}

ShaderProgramSources Shader::ParseShader(const std::string& filepath) {
    std::ifstream file(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(file, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        };
    }
    return { ss[0].str(), ss[1].str() };
}