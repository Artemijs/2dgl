#version 400 core



out vec4 FragColor;
in vec2 uv;


uniform sampler2D tex0;
uniform vec4 color;

uniform vec4 borderColor;
uniform vec2 size;
uniform float borderSize;

void main(){
	
	vec4 texCol = texture(tex0, uv);
	float brdrW = 10.0f/100.f;
	
	int on =0;
	if(uv.x <= brdrW || uv.x >= 1.0f-brdrW){
		 on = 1;
	
	}	
	FragColor = (texCol * color) * (1 - on) + vec3(1, 0, 1)* on;
}
