#version 400 core   

layout (location = 0) in vec3 vertPos;   
//layout(location = 1) in vec3  in_color;
layout (location = 1) in vec2 in_uv;


uniform vec2 uv_offset;
uniform vec2 uv_scale;


uniform mat4 model;
uniform mat4 proj;

//this is for the offset and scale of ui elements inside the render node
out vec2 uv;
//this is for the border
out vec2 oldUV;

void main(){
	gl_Position =   proj * (model) * vec4(vertPos, 1.0);

	uv = vec2(0.0f, 0.0f);
	uv.x = (in_uv.x ) * uv_scale.x + uv_offset.x;
	uv.y = (in_uv.y ) * uv_scale.y + uv_offset.y;

	oldUV = in_uv;



}