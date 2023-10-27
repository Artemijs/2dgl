#version 400 core




//final output color
out vec4 FragColor;

//texture positions interpolated from the vertex shader
in vec2 uv;

//the main texture of the tile map that is edited on the cpu side
uniform sampler2D tex0;

//overall ambient color of the object
uniform vec4 color;

//GRID VARIABLES
uniform float _tileSize;//tile size is sent to the shader in local uv space
uniform unsigned int _gridLineSize;
uniform vec3 _gridColor;

//HIGHLIGHT VARIABLES
uniform unsigned int _outlineSize;
uniform vec3 _outlineColor;


//This function calculates weather or not the current fragment should be colored
//the color is stored in glc(gridLineColor) as either 1 or 0
void GetGridLine(out unsigned int glc){
	
}


void main(){

	vec4 texCol = texture(tex0, uv);
	
	FragColor = (texCol * color);
}
