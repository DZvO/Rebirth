#pragma once
/*
// Basic 2D texture. Keeps track of the texture ID
// as well as the texture properties
class Texture
unsigned int m_width;
unsigned int m_height;
GLuint m_textureID;
GLenum m_minFilter;
GLenum m_magFilter;
GLenum m_wrapS;
GLenum m_wrapT;
void bind(GLuint slot); // Binds the texture to the given slot
*/
class CTexture
{
private:
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mTextureID;
	unsigned int mMinFilter;
	unsigned int mMagFilter;
	unsigned int mWrapS;
	unsigned int mWrapT;

public:
	CTexture();
	~CTexture();

	void bind(unsigned int slot);
};

