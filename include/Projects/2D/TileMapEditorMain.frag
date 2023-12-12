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
	uniform vec3 _outlineColor;
	uniform vec2 _tileId;

//This function calculates weather or not the current fragment should be colored
//the color is stored in glc(gridLineColor) as either 1 or 0
	
	void GetGridLine(out uint glc){
		float scale = 100.0f;
		vec2 t_uv = uv * scale;
		
		float tsTrans = _tileSize * scale;

		vec2 sPos = trunc(t_uv/ tsTrans);		
		sPos *= tsTrans;
		
		sPos /= scale;

		vec2 halfLine = vec2(_gridLineSize * 0.5f, _gridLineSize * 0.5f);
		
		vec2 endPos = sPos + halfLine;
		vec2 sPos2 = sPos + _tileSize - halfLine;

		if(uv.x >= sPos.x && uv.x <= endPos.x || uv.x >= sPos2.x && uv.x <= (sPos + _tileSize).x )
			glc = 1;
		else {
			if(uv.y >= sPos.y && uv.y <= endPos.y || uv.y >= sPos2.y && uv.y <= (sPos + _tileSize).y)
				glc = 1;
			else
				glc = 0;
		}
		

	}

	//check if pixels inside selected tile
	void GetHighlight(out uint isHigh){

		float scale = 100.0f;

		vec2 sPos = trunc((uv * scale) / (_tileSize * scale));		
		sPos *= (_tileSize * scale);
		
		sPos /= scale;

		if(uv.y >= _tileId.x && uv.y <= _tileId.x + _tileSize
		  && uv.x >= _tileId.y && uv.x <= _tileId.y + _tileSize){
			isHigh = 1;
		}
		else 
			isHigh = 0;
	}


	void main(){

		vec4 texCol = texture(tex0, uv) * color;

		uint glc = 0;
		uint isHigh = 1;

		GetGridLine(glc);
		GetHighlight(isHigh);

		isHigh *= glc;

		vec4 gridCol = vec4(_gridColor, 1.0f) * (glc - isHigh);
		vec4 highCol = vec4(_outlineColor, 1.0f) * (isHigh);

		texCol *= (1 - glc);
		
		FragColor = texCol + gridCol + highCol;
		
	}
