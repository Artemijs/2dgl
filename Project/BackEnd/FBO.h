#ifndef FBO_H
#define FBO_H
#include <glad/glad.h>


class FBO {
private:

	unsigned int _rbo;
	void CreateTexture(int width, int height);
	void CreateRenderBuffer(int width, int height);
	void AttachFboAttachments();
public :
	unsigned int _fbo;
	unsigned int _fboTex;
	FBO();
	FBO(int width, int height);
	~FBO();
	//void Bind();
	//void Unbind();
};
#endif