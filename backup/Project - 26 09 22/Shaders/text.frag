#version 400 core

out vec4 FragColor;

in vec2 uv;
in vec4 pos;

uniform vec2 spaceSize;
uniform vec2 charSize;
uniform sampler2D tex0;

void main(){

	vec4 texCol = texture(tex0, uv);
	//FragColor = texCol;//(pos + vec4(1,1,1,1))/2;
	vec4 col = (vec4(abs(pos.x), abs(pos.y), (abs(pos.y)+abs(pos.x))/2, 1) + texCol)/2;
	FragColor = texCol;//vec4(offX, 0,0,1);
}
