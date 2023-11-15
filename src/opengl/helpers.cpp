#include "helpers.h"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line <<std::endl;
        const auto& err_string = glewGetErrorString(error);
        std::cout << err_string << std::endl;
        return false;
    }
    return true;
}