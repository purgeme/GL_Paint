#include <cstdio>
#include <gtkmm-4.0/gtkmm.h>
#include <GL/glew.h>

#include "opengl/renderer.h"
#include "opengl/vertexBuffer.h"
#include "opengl/vertexBufferLayout.h"
#include "opengl/indexBuffer.h"
#include "opengl/vertexArray.h"
#include "opengl/shader.h"

class PaintArea : public Gtk::GLArea
{
    public:
        PaintArea();
        ~PaintArea();
        Gtk::GLArea *gl_area;
        struct ShaderProgramSource;
        void OnRealize();
        bool OnRender(const Glib::RefPtr<Gdk::GLContext>& context);
        void OnUnRealize();
        float _positions[8] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        };
        unsigned int _indices[6] = {
            0, 1, 2,
            2, 3, 0
        };
    private:
        static ShaderProgramSource ParseShader(const std::string& filename);
        static unsigned int CompileShader(unsigned int type, const std::string& source);
        static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        Shader *_program;
        VertexArray *_vao;
        VertexBuffer *_vbo;
        IndexBuffer *_ibo;
        Renderer *renderer;
};

PaintArea::PaintArea()
{
    gl_area = new Gtk::GLArea();
    gl_area->set_auto_render(true);
    // connect to the "render" signal
    gl_area->signal_render().connect(sigc::mem_fun(*this, &PaintArea::OnRender), false);
    gl_area->signal_realize().connect(sigc::mem_fun(*this, &PaintArea::OnRealize), false);

    // _vao = new VertexArray();
    // _vbo = new VertexBuffer(_positions, 4 * 2 * sizeof(float));
    // _ibo = new IndexBuffer(_indices, 6);
    // _program = new Shader("res/Basic.shader");
    // renderer = new Renderer();
}

PaintArea::~PaintArea()
{

}

struct PaintArea::ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

void PaintArea::OnRealize()
{
    gl_area->make_current();
    // if(glewInit() != GLEW_OK)
    //     std::cout << "Error!" << std::endl;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    // gl_area->make_current();
    // // if(glewInit() != GLEW_OK)
    // //     std::cout << "Error!" << std::endl;
    // GLenum err = glewInit();
    // if (GLEW_OK != err)
    // {
    //   /* Problem: glewInit failed, something is seriously wrong. */
    //   fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    // }

    // glGenVertexArrays(1, &_vao);
    // glBindVertexArray(_vao);

    // glGenBuffers(1, &_vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), _positions, GL_STATIC_DRAW);

    // glGenBuffers(1, &_ibo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    // ShaderProgramSource source = ParseShader("res/Basic.shader");
    // _program = CreateShader(source.VertexSource, source.FragmentSource);
    // glUseProgram(_program);

    // VertexBufferLayout layout;
    // layout.Push<float>(2);
    // _vao->AddBuffer(*_vbo, layout);

    // _vao->Bind();
    // _program->Bind();

    // float r = 0.0f;
    // float increment = 0.05f;

    // _program->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    // _program->UnBind();
    // _ibo->UnBind();
    // _vbo->UnBind();
    // _vao->UnBind();

}

bool PaintArea::OnRender(const Glib::RefPtr<Gdk::GLContext>& context)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);

    // glBindVertexArray(_Vao);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
    // // gl_area->queue_render();

    return true;
}