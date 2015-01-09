#include "ShaderProgram.h"


CShaderProgram::CShaderProgram()
{
}


CShaderProgram::~CShaderProgram()
{
}

void CShaderProgram::bind()
{
	glUseProgram(mGLID);
}
