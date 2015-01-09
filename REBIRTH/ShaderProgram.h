#pragma once
#include <string>
#include <GL/glew.h>

class CShaderProgram
{
private:
	unsigned int mGLID;
public:
	CShaderProgram();
	~CShaderProgram();

	bool loadFragment(std::string path);
	bool loadVertex(std::string path);
	bool compile();

	void bind();

	void setUniform(std::string uName, float uVal);
};

