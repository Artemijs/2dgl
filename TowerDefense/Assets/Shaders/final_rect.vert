#version 400 core   

layout (location = 0) in vec3 vertPos;   
layout (location = 1) in vec2 in_uv;



out vec2 uv;

void main(){
	//gl_Position =   proj * (model) * vec4(vertPos, 1.0);
	gl_Position = vec4(vertPos, 1.0);
	uv = (in_uv );
}