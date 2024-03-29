#include "Game/FBOComponent.h"
#include <iostream>
#include "Util/Utility.h"
#include "Graphics/Renderer.h"
const unsigned int FBOComponent::_component_id = Utility::GetID<FBOComponent>();
FBOComponent::FBOComponent()  {
	
	Renderer* r = Renderer::instance();

	int width = (int)(r->GetWindowSize().x);
	int height = (int)(r->GetWindowSize().y);

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
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_clearColor = Vec3(0.2f, 0.13f, 0.17f);

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

	//create the render buffer
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	//attach attachments to the frame buffer object
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fboTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

	_clearColor = Vec3(0.2f, 0.13f, 0.17f);
}
const unsigned int FBOComponent::ID() const { return _component_id; }

void FBOComponent::Clear() const {

	glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

}


void FBOComponent::SetClearColor(Vec3 col) {
	_clearColor = col;

}


void SetTextSize(const unsigned int width, const unsigned int height) {
	


}