#version 400 core

out vec4 FragColor;
in vec2 uv;
in vec3 color;

uniform sampler2D tex0;

void main(){
	vec4 texCol = texture(tex0, uv);

	FragColor = texCol;
}
