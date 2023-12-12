#version 400 core

out vec4 FragColor;
in vec2 uv;


uniform vec2 iResolution;
uniform float iTime ;
uniform vec4 color;


vec3 palette(float t){
	vec3 a = vec3(0.5f, 0.5f, 0.5f);
	vec3 b = vec3(0.5f, 0.5f, 0.5f);
	vec3 c = vec3(1.0f, 1.0f, 1.0f);
	vec3 d = vec3(0.263f, 0.416f, 0.557f);
	
	return a + b*cos(6.28318*(c*t+d));
}


void main(){
	vec4 outColor = vec4(0,0,0,1);
	
	vec2 fragcoord = (gl_FragCoord.xy * 2 -iResolution.xy) / iResolution.y;
	vec2 tempcoord = fragcoord;
	vec3 finalCol = vec3(0);

	for(int i = 0; i < 5; i++){
		fragcoord = fract(fragcoord * 1.5f)-0.5f;

		float d = length(fragcoord) * exp(-length(tempcoord));

		vec3 col = palette(length(tempcoord) +i * 4 + iTime *2);
	
		d = sin(d * 8 + iTime)/8;
		d = abs(d);

		//d = smoothstep(0.0f, 0.1f, d);
		//d = 0.01f/d;
		d = pow(0.01/d, 1.8);

		finalCol += col * d;
	}
	
	FragColor = (vec4(finalCol, 1.0f));
}
