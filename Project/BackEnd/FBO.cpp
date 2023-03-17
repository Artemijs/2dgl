#include "FBO.h"
#include <iostream>
FBO::FBO() {

	int width = 0;
	int height = 0;
	//create fbo
	glGenFramebuffers(1, &_fbo);
	CreateTexture(width, height);
	CreateRenderBuffer(width, height);
	AttachFboAttachments();

	

	
	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error " << fboStatus << "\n";
	//36054 comething is uninitisalized
	//36057 not all attached images have the same width and height
	//36055 no images attached to the framebuffer
	//36061 the combination of internal formats of the attached imagesviolates an implementation dependant set of restrictions
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

}
FBO::FBO(int width, int height) {

	//create fbo
	glGenFramebuffers(1, &_fbo);
	CreateTexture(width, height);
	CreateRenderBuffer(width, height);
	AttachFboAttachments();




	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error " << fboStatus << "\n";
	//36054 comething is uninitisalized
	//36057 not all attached images have the same width and height
	//36055 no images attached to the framebuffer
	//36061 the combination of internal formats of the attached imagesviolates an implementation dependant set of restrictions
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);

}
FBO::~FBO() {
	glDeleteTextures(1, &_fboTex);
	glDeleteRenderbuffers(1, &_rbo);
	glDeleteFramebuffers(1, &_fbo);
}

void FBO::CreateTexture(int width, int height) {
	//create texture attachment
	glGenTextures(1, &_fboTex);
	glBindTexture(GL_TEXTURE_2D, _fboTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}
void FBO::CreateRenderBuffer(int width, int height) {
	//create the render buffer attachment

	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

}
void FBO::AttachFboAttachments() {
	//attach the texture and render buffer 
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fboTex, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

}
/*void FBO::Bind() {

}
void FBO::Unbind() {

}*/
