#version 400 core   

layout (location = 0) in vec3 vertPos;   
//layout(location = 1) in vec3  in_color;
layout (location = 1) in vec2 in_uv;


uniform vec2 uv_offset;
uniform vec2 uv_scale;


uniform mat4 model;
uniform mat4 proj;

out vec2 uv;


void main(){
	gl_Position =   proj * (model) * vec4(vertPos, 1.0);

	uv = vec2(0.0f, 0.0f);
	uv.x = (in_uv.x ) * uv_scale.x;
	uv.y = (in_uv.y ) * uv_scale.y;
	//uv.y = (in_uv.y );



}