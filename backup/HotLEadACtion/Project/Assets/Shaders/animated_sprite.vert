#version 400 core   

layout (location = 0) in vec3 vertPos;   
layout(location = 1) in vec3  in_color;
layout (location = 2) in vec2 in_uv;



uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 scale;

uniform mat4 view;
uniform mat4 proj;
uniform vec2 uv_scale;
uniform vec2 uvOff;

out vec3 color;
out vec2 uv;

void main(){

	gl_Position =   proj * (transform * rotation * scale) * vec4(vertPos, 1.0);
	color = in_color;
	uv = vec2(0.0f, 0.0f);
	uv.x = (in_uv.x  + uvOff.x) * uv_scale.x;
	uv.y = (in_uv.y + uvOff.y) * uv_scale.y;
}