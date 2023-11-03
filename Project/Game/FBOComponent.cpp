#include "FBOComponent.h"
#include <iostream>
#include "../Util/Utility.h"
const unsigned int FBOComponent::_component_id = Utility::GetID<FBOComponent>();
FBOComponent::FBOComponent()  {
	int width = 0;
	int height = 0;
	printf("width height not set of frame buffer component\n");
	//create the fbo
	glGenFramebuffers(1, &_fbo);
	//create the texture that is drawn to
	glGenTextures(1, &_fboTexture);
	glBindTexture(GL_TEXTURE_2D, _fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//create therender buffer
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	//attach attachments to the frame buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fboTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
FBOComponent::~FBOComponent() {
	printf("deleting fbo compo comonent\n");
	glDeleteTextures(1, &_fboTexture);
	glDeleteRenderbuffers(1, &_rbo);
	glDeleteFramebuffers(1, &_fbo);

}
FBOComponent::FBOComponent(const unsigned int width, const unsigned int height) {
	//printf("width height not set of frame buffer component\n");
	//create the fbo
	glGenFramebuffers(1, &_fbo);
	//create the texture that is drawn to
	glGenTextures(1, &_fboTexture);
	glBindTexture(GL_TEXTURE_2D, _fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//create therender buffer
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	//attach attachments to the frame buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fboTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
}
const unsigned int FBOComponent::ID() const { return _component_id; }