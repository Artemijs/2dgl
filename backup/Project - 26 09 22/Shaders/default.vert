#version 400 core   

layout (location = 0) in vec3 vertPos;   
layout(location = 1) in vec3  in_color;
layout (location = 2) in vec2 in_uv;



uniform mat4 model;
uniform mat4 proj;


out vec3 color;
out vec2 uv;

void main(){
	//gl_Position =   proj * model * vec4(vertPos, 1.0);
	gl_Position =   proj * model * vec4(vertPos, 1.0);
	color = in_color;
	uv = (in_uv );
}