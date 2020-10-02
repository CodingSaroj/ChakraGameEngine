#include "OpenGL4Common.hpp"

namespace Chakra
{
    void CheckGLError(const char * functionCall)
    {
        GLenum error = glGetError();

        switch (error)
        {
            case GL_NO_ERROR:
            {
                break;
            }

            case GL_INVALID_ENUM:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_ENUM in function call `", functionCall, "`.");
                break;
            }
            
            case GL_INVALID_VALUE:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_VALUE in function call `", functionCall, "`.");
                break;
            }
            
            case GL_INVALID_INDEX:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_INDEX in function call `", functionCall, "`.");
                break;
            }

            case GL_INVALID_OPERATION:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_OPERATION in function call `", functionCall, "`.");
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_FRAMEBUFFER_OPERATION in function call `", functionCall, "`.");
                break;
            }

            case GL_OUT_OF_MEMORY:
            {
                CHK_ERROR("Renderer::OpenGL4", "GL_INVALID_OUT_OF_MEMORY in function call `", functionCall, "`.");
                break;
            }

            default:
            {
                CHK_ERROR("Renderer::OpenGL4", "Unhandled enum value ", error, " in function call `", functionCall, "`.");
                break;
            }
        }
    }
}
