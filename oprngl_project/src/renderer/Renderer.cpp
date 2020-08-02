#include "pch.h"
#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] " << error << " Function: " << function << " File: " << file << " Line: " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    GLCall(shader.Bind());
    GLCall(va.Bind());
    GLCall(ib.Bind());
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::DrawSquare(const VertexArray& va, const Shader& shader) const {
    GLCall(shader.Bind());
    GLCall(va.Bind());
    for (int i = 1; i <= 6; i++)
    {
        //glUniform1i(shader.GetUniformLocation("face"), i);
        GLCall(glDrawArrays(GL_TRIANGLES, (i-1) * 6, 6));
    }
}

void Renderer::Clear() const {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
