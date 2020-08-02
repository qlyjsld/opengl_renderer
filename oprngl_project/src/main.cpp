#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "renderer/Renderer.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/shader.h"
#include "texture.h"
#include "mvp.h"
#include "camera.h"
#include "global.h"
#include "globalVar.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/stb_image/stb_image.h"

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, ":)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "error" << std::endl;
    }

    glViewport(0, 0, 1920, 1080);
    std::cout << glGetString(GL_VERSION) << std::endl;

    stbi_set_flip_vertically_on_load(true);

    renderPrepare(window);

    glm::vec3 box_pos[7]{
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 2.0f),
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, -2.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -2.0f)
    };
    
    glm::vec3 light_pos[6]{
        glm::vec3(10.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 10.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 10.0f),
        glm::vec3(-10.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, -10.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -10.0f)
    };

    float square[192] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    };

    unsigned int square_index[36] = {
         0,  1,  2,
         0,  2,  3,
         4,  5,  6,
         4,  6,  7,
         8,  9, 10,
         8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };

    {VertexArray box_va;
    VertexBuffer box_vb(&square[0], len(square) * sizeof(float));
    IndexBuffer box_ib(&square_index[0], 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    box_va.AddBuffer(layout);

    Shader light_shader("res/shader/light.shader");
    Shader box_shader("res/shader/box.shader");
    box_shader.updateUniform<int>("material.diffuse", 0);
    box_shader.updateUniform<int>("material.specular", 1);
    box_shader.updateUniform<float>("material.shininess", 1.0);

    for (unsigned int i = 0; i < len(light_pos); i++) {
        box_shader.updateUniform<glm::vec3>("pointlight[" + std::to_string(i) + "].position", light_pos[i]);
        box_shader.updateUniform<glm::vec3>("pointlight[" + std::to_string(i) + "].ambient", glm::vec3(0.2f, 0.2, 0.2f));
        box_shader.updateUniform<glm::vec3>("pointlight[" + std::to_string(i) + "].diffuse", glm::vec3(0.5f, 0.5, 0.5f));
        box_shader.updateUniform<glm::vec3>("pointlight[" + std::to_string(i) + "].specular", glm::vec3(0.8f, 0.8f, 0.8f));
        box_shader.updateUniform<float>("pointlight[" + std::to_string(i) + "].constant", 1);
        box_shader.updateUniform<float>("pointlight[" + std::to_string(i) + "].linear", 0.7);
        box_shader.updateUniform<float>("pointlight[" + std::to_string(i) + "].quadratic", 1.8);
    }

    box_shader.updateUniform<glm::vec3>("dirlight.direction", glm::vec3(0.0f, -1.0, 0.0f));
    box_shader.updateUniform<glm::vec3>("dirlight.ambient", glm::vec3(0.2f, 0.2, 0.2f));
    box_shader.updateUniform<glm::vec3>("dirlight.diffuse", glm::vec3(0.5f, 0.5, 0.5f));
    box_shader.updateUniform<glm::vec3>("dirlight.specular", glm::vec3(0.8f, 0.8f, 0.8f));

    box_shader.updateUniform<float>("spotlight.cutoff", glm::cos(glm::radians(12.5)));
    box_shader.updateUniform<float>("spotlight.outercutoff", glm::cos(glm::radians(17.5)));
    box_shader.updateUniform<glm::vec3>("spotlight.ambient", glm::vec3(0.2f, 0.2, 0.2f));
    box_shader.updateUniform<glm::vec3>("spotlight.diffuse", glm::vec3(0.5f, 0.5, 0.5f));
    box_shader.updateUniform<glm::vec3>("spotlight.specular", glm::vec3(0.8f, 0.8f, 0.8f));
    box_shader.updateUniform<float>("spotlight.constant", 1);
    box_shader.updateUniform<float>("spotlight.linear", 0.045);
    box_shader.updateUniform<float>("spotlight.quadratic", 0.0075);

    box_shader.updateUniform<glm::vec3>("lightcolor", glm::vec3(1.0f, 1.0f, 1.0f));

    Texture box_diffuse("res/texture/woodbox.jpg");
    Texture box_specular("res/texture/woodbox_specular.jpg");

    mvp mvp;
    defaultCamera.setAllcamerapos(glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3(0.0f, -0.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Renderer renderer;

    const char* glsl_version = "#version 330 core";

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        defaultCamera.processInput(window);

        box_shader.updateUniform<glm::vec3>("viewpos", defaultCamera.cameraPos);
        box_shader.updateUniform<glm::vec3>("spotlight.position", defaultCamera.cameraPos);
        box_shader.updateUniform<glm::vec3>("spotlight.direction", defaultCamera.cameraFront);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();}

        box_diffuse.Bind(0);
        box_specular.Bind(1);
        for (unsigned int i = 0; i < len(box_pos); i++) {
            mvp.reset();
            mvp.rotate(mvp.model, glfwGetTime(), glm::vec3(0.2f, 0.3f, 0.8f));
            mvp.translate(mvp.model, box_pos[i]);
            mvp.rotate(mvp.model, glfwGetTime(), glm::vec3(0.8f, 0.3f, 0.2f));
            mvp.view = glm::mat4(defaultCamera.lookat(defaultCamera.cameraPos, defaultCamera.cameraPos + defaultCamera.cameraFront, defaultCamera.cameraUp));
            mvp.perspective(mvp.projection, glm::radians(fov), 1920.0 / 1080.0f, 0.1f, 100.0f);
            mvp.updateUniform(box_shader);
            renderer.Draw(box_va, box_ib, box_shader);
        }

        for (unsigned int i = 0; i < len(light_pos); i++) {
            mvp.reset();
            mvp.translate(mvp.model, light_pos[i]);
            mvp.view = glm::mat4(defaultCamera.lookat(defaultCamera.cameraPos, defaultCamera.cameraPos + defaultCamera.cameraFront, defaultCamera.cameraUp));
            mvp.perspective(mvp.projection, glm::radians(fov), 1920.0 / 1080.0f, 0.1f, 100.0f);
            mvp.updateUniform(light_shader);
            renderer.Draw(box_va, box_ib, light_shader);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }}
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
