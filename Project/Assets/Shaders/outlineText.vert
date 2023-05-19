#version 400 core   

layout (location = 0) in vec3 vertPos;   
layout (location = 1) in vec2 in_uv;



uniform mat4 model;

uniform mat4 view;
uniform mat4 proj;

out vec2 uv;
out vec4 pos;

void main(){
	pos = vec4(vertPos, 1.0f);
	gl_Position = proj * (model) * vec4(vertPos, 1.0);
	uv = vec2(in_uv.x, 1 - in_uv.y);


}