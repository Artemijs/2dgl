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
	uniform float _gridLineSize;
	uniform vec3 _gridColor;

//HIGHLIGHT VARIABLES
	uniform float _outlineSize;
	uniform vec3 _outlineColor;


//This function calculates weather or not the current fragment should be colored
//the color is stored in glc(gridLineColor) as either 1 or 0
	
	void GetGridLine(out uint glc){
		float scale = 100.0f;
		vec2 t_uv = uv * scale;
		
		float tsTrans = _tileSize * scale;

		vec2 sPos = trunc(t_uv/ tsTrans);		
		sPos *= tsTrans;
		
		sPos /= scale;
		vec2 endPos = sPos + vec2(_gridLineSize, _gridLineSize);

		if(uv.x >= sPos.x && uv.x <= endPos.x)
			glc = 1;
		else {
			if(uv.y >= sPos.y && uv.y <= endPos.y)
				glc = 1;
			else
				glc = 0;
		}
		

	}
	void main(){

		vec4 texCol = texture(tex0, uv);

		uint glc = 0;
		GetGridLine(glc);
		//FragColor = vec4(_gridColor, 1.0f) * glc;
		FragColor = ((texCol * color) +  vec4(_gridColor, 1.0f) * glc);
	}
