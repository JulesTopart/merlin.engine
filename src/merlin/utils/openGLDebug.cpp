#include "pch.h"
#include "merlin/utils/openGLDebug.h"

namespace Merlin {

	void openGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			{
				LOG_ERROR("OpenGL Debug") << message << Console::endl;
				//GLCORE_ASSERT(false, "OpenGL", "GL_DEBUG_SEVERITY_HIGH");
			}
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
				LOG_WARN("OpenGL Debug") << message << Console::endl;
			break;
		case GL_DEBUG_SEVERITY_LOW:
				LOG_INFO("OpenGL Debug") << message << Console::endl;
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
				//LOG_TRACE("OpenGL Debug") << message << Console::endl;
			break;
		default:
			;// LOG_TRACE("OpenGL Debug") << message << Console::endl;
			break;
		}
	}

	void enableGLDebugging()
	{
		glDebugMessageCallback(openGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

}