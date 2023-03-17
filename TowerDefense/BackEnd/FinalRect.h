#ifndef FINAL_RECT_H
#define FINAL_RECT_H

#include "VAO.h"
#include "../Graphics/ShaderClass.h"


class FinalRect
{
private :
	/*GLfloat _vertices[30] = {
		//verices					colors				//uvs
		-0.5f,  -0.5f,  -1.0f,			0.0f, 0.0f, //lower left

		-0.5f,   0.5f,	-1.0f,			0.0f, 1.0f,//upper left 

		 0.5f,	 0.5f,	-1.0f,			1.0f, 1.0f, //upper right

		 -0.5f,	-0.5f,	-1.0f,			1.0f, 0.0f, //loaer left
		 0.5f,	0.5f,	-1.0f,			1.0f, 0.0f, //upper right
		 0.5f,	-0.5f,	-1.0f,			1.0f, 0.0f //lower right
	};*///b left b right t right
	GLfloat _vertices[30] = {
		//verices					//uvs
		-1,		-1,		-1,		0.0f, 0.0f, //lower left
		-1,		1,		-1,		0.0f, 1.0f, //top left 
		1,		1,		-1,		1.0f, 1.0f, //top right

		1,		1,		-1,		1.0f, 1.0f, //top right
		1,		-1,		-1,		1.0f, 0.0f,  //bot right
		-1,		-1,		-1,		0.0f, 0.0f //lower left
		
		
		
	};
	Shader* _shader;
public :
	GLuint _vao;
	GLuint _vbo;
	FinalRect();
	~FinalRect();
	void Bind();
	void Unbind();
	
};
#endif

