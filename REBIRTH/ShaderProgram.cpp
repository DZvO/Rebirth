#include "ShaderProgram.h"


CShaderProgram::CShaderProgram()
{
	mGLID = glCreateProgram();
	mFragID = glCreateShader(GL_FRAGMENT_SHADER);
	mVertID = glCreateShader(GL_VERTEX_SHADER);
}


CShaderProgram::~CShaderProgram()
{
	glUseProgram(0);
	glDeleteShader(mGLID);
	glDeleteShader(mFragID);
	glDeleteShader(mVertID);

}

void CShaderProgram::bind()
{
	glUseProgram(mGLID);
}

bool CShaderProgram::loadFragment(std::string path)
{
	mFragPath = path;
	std::string * source = new std::string();
	if (loadFile(path, source) == false)
		return false;

	const char* c_str = source->c_str();
	glShaderSource(mFragID, 1, &c_str, NULL);

	delete source;
	return true;
}

bool CShaderProgram::loadVertex(std::string path)
{
	mVertPath = path;
	std::string * source = new std::string();
	if (loadFile(path, source) == false)
		return false;

	const char* c_str = source->c_str();
	glShaderSource(mVertID, 1, &c_str, NULL);
	
	delete source;
	return true;
}

bool CShaderProgram::compile()
{
	if (mVertPath == "default") {
		glShaderSource(mVertID, 1, &mDefaultVert, NULL);
		printf("Using default vertex program");
	}
	if (mFragPath == "default") {
		glShaderSource(mFragID, 1, &mDefaultFrag, NULL);
		printf("Using default fragment program");
	}

	int ecode;
	char * emsgbuffer = new char[1024];
	int emsglength = 0;

	glCompileShader(mVertID);
	glGetShaderiv(mVertID, GL_COMPILE_STATUS, &ecode);
	if (ecode == GL_FALSE) {
		glGetShaderInfoLog(mVertID, 1024, &emsglength, emsgbuffer);
		printf("Error while compiling vertex shader %s ; %s\n",
			mVertPath.c_str(), emsgbuffer);
		return false;
	}

	glCompileShader(mFragID);
	glGetShaderiv(mFragID, GL_COMPILE_STATUS, &ecode);
	if (ecode == GL_FALSE) {
		glGetShaderInfoLog(mFragID, 1024, &emsglength, emsgbuffer);
		printf("Error while compiling fragment shader %s ; %s\n",
			mFragPath.c_str(), emsgbuffer);
		return false;
	}


	glAttachShader(mGLID, mFragID);
	glAttachShader(mGLID, mVertID);

	glLinkProgram(mGLID);
	glGetProgramiv(mGLID, GL_LINK_STATUS, &ecode);
	if (ecode == GL_FALSE) {
		glGetProgramInfoLog(mGLID, 1024, &emsglength, emsgbuffer);
		printf("Error while linking shaderprogram (%s + %s) ; %s\n",
			mVertPath.c_str(), mFragPath.c_str(), emsgbuffer);
		return false;
	}
	glValidateProgram(mGLID);
	glGetProgramiv(mGLID, GL_VALIDATE_STATUS, &ecode);
	if (ecode == GL_FALSE) {
		glGetProgramInfoLog(mGLID, 1024, &emsglength, emsgbuffer);
		printf("Error while validating shaderprogram (%s + %s) ; %s\n",
			mVertPath.c_str(), mFragPath.c_str(), emsgbuffer);
		return false;
	}

	return true;
}

bool CShaderProgram::loadFile(std::string path, std::string * output)
{
	std::ifstream file(path, std::ios::binary);
	if (file.good() == false) {
		printf("Couldn't open file %s\n");
		return false;
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();

	*output = buffer.str();

	return true;
}

int CShaderProgram::getref()
{
	return mGLID;
}

int CShaderProgram::getAttribLocation(std::string attribName)
{
	if (mAttributes.count(attribName) == 0)
		mAttributes[attribName] = glGetAttribLocation(mGLID, attribName.c_str());
	return mAttributes[attribName];
}
