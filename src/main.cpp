// Import libraries
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if !defined(__linux__)
#include <windows.h>
#endif
#include <FreeImage.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "opengl/renderer.h"
#include "opengl/vertexBuffer.h"
#include "opengl/vertexBufferLayout.h"
#include "opengl/indexBuffer.h"
#include "opengl/vertexArray.h"
#include "opengl/shader.h"
#include "opengl/helpers.h"

// ImGui vars
static ImVec4 clearColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
static ImVec4 paintColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float my_color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
bool showWindows = true;

// Dimensions
const float w_H = 720.0f;
const float w_W = 1280.0f;
const float leftPanel_Hp = 1.0f;
const float leftPanel_Wp = 0.1f;
const float colorSelector_H = 0.3f;
const float drawingArea_Hp = 1.0f;
const float drawingArea_Wp = 0.9f;

// Drawing framebuffer and texture
unsigned int drawingBuffer;
unsigned int drawingTexture;

void draw(float x, float y);

int main(int argc, char **argv)
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    GLFWwindow *window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(w_W, w_H, "GL_Paint", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        return -1;

    // Create framebuffer
    GLCALL(glGenFramebuffers(1, &drawingBuffer));
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer));

    // Create drawing texture
    glGenTextures(1, &drawingTexture);
    glBindTexture(GL_TEXTURE_2D, drawingTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, drawingArea_Wp * w_W, drawingArea_Hp * w_H, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create shader for the drawing
    Shader shader("res/Basic.shader");
    shader.Bind();
    float r = 0.0f;
    float increment = 0.05f;
    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
    shader.UnBind();

    // Setup ImGui library
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Setup drawing area
    glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 500, 0);
    glPointSize(3.0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Setup ImGui and windows
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Color selector
        ImGui::Begin("Color picker", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(leftPanel_Wp * w_W, (colorSelector_H)*leftPanel_Hp * w_H));
        if (ImGui::ColorButton("Color Picker", paintColor))
            std::cout << "Color picker" << std::endl;
        ImGui::End();

        // Brush selector
        ImGui::Begin("Brush Selector", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(0, colorSelector_H * leftPanel_Hp * w_H));
        ImGui::SetWindowSize(ImVec2(leftPanel_Wp * w_W, (1 - colorSelector_H) * leftPanel_Hp * w_H));
        if (ImGui::Button("Square"))
            std::cout << "Square button" << std::endl;
        if (ImGui::Button("Circle"))
            std::cout << "Circle button" << std::endl;
        if (ImGui::Button("Triangle"))
            std::cout << "Triangle button" << std::endl;
        ImGui::End();

        // Drawing area
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Drawing Area", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(leftPanel_Wp * w_W, 0));
        ImGui::SetWindowSize(ImVec2(drawingArea_Wp * w_W, drawingArea_Hp * w_H));
        ImGui::Image((void *)drawingTexture, ImVec2(drawingArea_Wp * w_W, drawingArea_Hp * w_H));
        ImGui::End();
        ImGui::PopStyleVar();

        // Actual code to draw
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            // if (ImGui::IsMouseHoveringRect(ImVec2((1 - drawingArea_Wp) * w_W, 0), ImVec2(w_W, drawingArea_Hp * w_H)))
            if (ImGui::IsMouseHoveringRect(ImVec2(0, 0), ImVec2(w_W, w_H)))
            {
                // Bind Framebuffer and bind the texture to that framebuffer
                glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);

                // Drawing part
                shader.Bind();
                shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

                ImVec2 mousePos = ImGui::GetMousePos();
                draw(mousePos.x-((1-drawingArea_Wp)*w_W), mousePos.y);

                if (r > 1.0f)
                    increment = -0.01f;
                else if (r < 0.0f)
                    increment = 0.01f;

                r += increment;
                shader.UnBind();
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            }
        }

        // Render ImGui stuff
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    glfwTerminate();

    // Shutdown ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // DeInitialize FreeImage library
    FreeImage_DeInitialise();

    return 0;
}

void draw(float cx, float cy)
{
    std::cout << "Mouse position: " << cx << ";" << cy << std::endl;
    // glClear(GL_COLOR_BUFFER_BIT);
    int num_segments = 50;
    int r = 5;
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii += 1)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle        
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex           
    }
    glEnd();
}