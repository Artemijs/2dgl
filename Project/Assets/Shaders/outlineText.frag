#version 400 core

out vec4 FragColor;

in vec2 uv;
in vec4 pos;

uniform sampler2D tex0;


float width = 0.5f;
float edge = 0.15f;

uniform float borderWidth;
float borderEdge = 0.1f;

uniform vec2 offset;

uniform vec3 color;
uniform vec3 outlineColor;
void main(){
	vec4 texCol = texture(tex0, uv);

	float distance = 1 - texture(tex0, uv).a;
	float a = 1.0f - smoothstep(width, width + edge, distance);

	float distance2 = 1 - texture(tex0, uv + offset).a;
	float outlineA = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	float totalA = a + (1.0 - a) * outlineA;
	vec3 overallColor = mix(outlineColor, color, a / totalA);
	if(totalA < 0.1f){
		discard;
	}
	FragColor = vec4(overallColor, totalA);
	//FragColor = vec4(0, 0, 0, 1);
}
