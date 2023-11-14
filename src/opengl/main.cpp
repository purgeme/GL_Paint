#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

int main(void)
{

    std::cout << "Test string";
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    va.Bind();

    Shader shader("res/Basic.shader");
    shader.Bind();


    float r = 0.0f;
    float increment = 0.05f;

    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    shader.UnBind();
    ib.UnBind();
    vb.UnBind();
    va.UnBind();

    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        renderer.Draw(va, ib, shader);
        if(r>1.0f)
            increment = -0.001f;
        else if(r<0.0f)
            increment = 0.001f;

        r+=increment;

        shader.UnBind();
        GLCALL(glfwSwapBuffers(window));

        GLCALL(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}