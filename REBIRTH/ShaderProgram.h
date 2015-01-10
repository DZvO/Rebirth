#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <GL/glew.h>


class CShaderProgram
{
private:
	unsigned int mGLID;
	unsigned int mFragID;
	unsigned int mVertID;
	std::string mFragPath = "default";
	std::string mVertPath = "default";

	const char* mDefaultFrag =
		"";
	const char* mDefaultVert =
		"";

	bool loadFile(std::string path, std::string * output);

	std::map<std::string, int> mAttributes;

public:
	CShaderProgram();
	~CShaderProgram();

	bool loadFragment(std::string path);
	bool loadVertex(std::string path);
	bool compile();

	void bind();

	int getref();

	void setUniform(std::string uName, float uVal);

	int getAttribLocation(std::string attribName);
};

