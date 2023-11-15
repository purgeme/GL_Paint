#pragma once

#include <GL/glew.h>
#include <iostream>

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

class Renderer
{
public:
    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};