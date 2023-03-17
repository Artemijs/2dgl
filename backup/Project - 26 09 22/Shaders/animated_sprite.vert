#version 400 core   

layout (location = 0) in vec3 vertPos;   
layout(location = 1) in vec3  in_color;
layout (location = 2) in vec2 in_uv;



uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec2 scale;
uniform vec2 uvOff;

out vec3 color;
out vec2 uv;

void main(){
	/*uvOff = vec2(0, 3);*/

	gl_Position =   proj * model * vec4(vertPos, 1.0);
	color = in_color;
	uv = vec2(0.0f, 0.0f);
	uv.x = (in_uv.x  + uvOff.x) * scale.x;
	uv.y = (in_uv.y + uvOff.y) * scale.y;

	/*uv = (in_uv + uvOff) * scale;*/
}