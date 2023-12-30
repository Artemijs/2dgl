#version 400 core



out vec4 FragColor;

in vec2 uv;
in vec2 oldUV;

uniform sampler2D tex0;
uniform vec4 color;

uniform vec4 borderColor;
uniform vec2 size;
uniform float borderSize;

void main(){
	
	vec4 texCol = texture(tex0, uv);
	float brdrW = borderSize/size.x;
	float brdrH = borderSize/size.y;
	
	int on = 0;
	if(oldUV.x <= brdrW || oldUV.x >= 1.0f - brdrW){
		 on = 1;
	}
	if(oldUV.y <= brdrH || oldUV.y >= 1.0f - brdrH){
		 on = 1;
	}
	FragColor = (texCol * color) * (1 - on) + borderColor * on;
	//FragColor =  vec4(1, 1, 1, 1) * on;
}
