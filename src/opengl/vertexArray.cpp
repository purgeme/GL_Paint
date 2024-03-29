#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "renderer.h"
#include "helpers.h"

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i=0; i<elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void*)offset));
        offset += VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
    GLCALL(glBindVertexArray(0));
}