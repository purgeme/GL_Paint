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
#include "Window.h"
#include "functions.h"
#include "variables.h"

// Drawing vars
int size_brush = 20;
bool hollow = false;
int shape[5] = { 0,1,2,3,4 };
int option = shape[line];

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
const float colorSelector_H = 0.2f;
const float brushSelector_H = 0.7f;
const float saveWindow_H = 0.1f;
const float drawingArea_Hp = 1.0f;
const float drawingArea_Wp = 0.9f;

// Drawing framebuffer and texture
unsigned int drawingBuffer;
unsigned int drawingTexture;

int main(int argc, char **argv)
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    Window window(w_W, w_H, "GL_Paint");

    glfwMakeContextCurrent(window.window);

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
    ImGui_ImplGlfw_InitForOpenGL(window.window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Setup drawing area
    glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, w_W, w_H, 0);
    glPointSize(3.0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (!glfwWindowShouldClose(window.window))
    {

        // Setup ImGui and windows
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Color selector
        ImGui::Begin("Color picker", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(leftPanel_Wp * w_W, colorSelector_H * leftPanel_Hp * w_H));
        if (ImGui::ColorButton("Color Picker", paintColor, 0, ImVec2(leftPanel_Wp*w_W-17, (colorSelector_H)*leftPanel_Hp*w_H-17))){
            std::cout << "Color picker" << std::endl;
            ImGui::OpenPopup("hi-picker");
        }
        if (ImGui::BeginPopup("hi-picker"))
        {
            ImGui::ColorPicker4("##picker", &paintColor.x, ImGuiColorEditFlags_None, NULL);
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(paintColor.x, paintColor.y, paintColor.z);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            ImGui::EndPopup();
        }
        ImGui::End();

        // Brush selector
        ImGui::Begin("Brush Selector", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(0, colorSelector_H * leftPanel_Hp * w_H));
        ImGui::SetWindowSize(ImVec2(leftPanel_Wp * w_W, brushSelector_H * leftPanel_Hp * w_H));
        if (ImGui::Button("Circle", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(paintColor.x, paintColor.y, paintColor.z);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            setShape(0);
        }
        if (ImGui::Button("Square", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(paintColor.x, paintColor.y, paintColor.z);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            setShape(1);
        }
        if (ImGui::Button("Triangle", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(paintColor.x, paintColor.y, paintColor.z);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            setShape(2);
        }
        if (ImGui::Button("Line", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(paintColor.x, paintColor.y, paintColor.z);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            setShape(3);
        }
        if (ImGui::Button("Eraser", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            setShape(4);
        } 
        ImGui::End();

        // Save button
        ImGui::Begin("Save Button", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(0, (colorSelector_H+brushSelector_H) * leftPanel_Hp * w_H));
        ImGui::SetWindowSize(ImVec2(leftPanel_Wp * w_W, (saveWindow_H) * leftPanel_Hp * w_H));
        if (ImGui::Button("Save Image", ImVec2(leftPanel_Wp*w_W-30, 0))){
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);
            saveScreenshot(w_W, w_H, drawingArea_Wp * w_W, drawingArea_Hp * w_H);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        } 
        ImGui::End();

        // Drawing area
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Drawing Area", &showWindows, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowPos(ImVec2(leftPanel_Wp * w_W, 0));
        ImGui::SetWindowSize(ImVec2(drawingArea_Wp * w_W, drawingArea_Hp * w_H));
        ImGui::Image((void *)drawingTexture, ImVec2(drawingArea_Wp * w_W, drawingArea_Hp * w_H));

        // Actual code to draw
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow))
        {
            // Bind Framebuffer and bind the texture to that framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, drawingBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drawingTexture, 0);

            // Drawing part
            ImVec2 mousePos = ImGui::GetMousePos();
            draw_pixel(mousePos.x-((1-drawingArea_Wp)*w_W), w_H-mousePos.y);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        glfwSwapBuffers(window.window);
        glfwPollEvents();

        ImGui::End();
        ImGui::PopStyleVar();

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