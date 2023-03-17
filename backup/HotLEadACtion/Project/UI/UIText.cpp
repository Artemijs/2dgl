#include "UIText.h"
#include <fstream>
#include "../Graphics/Renderer.h"

UIText::UIText(Vec3 position, float angle, int fontSize, std::string txt, int maxCharPerLine):
	Graphic("Assets/Fonts/arial.png", position, Vec3(1, 1, 1), angle), _text(txt), _maxCharsPerLine(maxCharPerLine), _fontSize(fontSize) {
	if (txt.length() == 0) {
		_text = " ";
	}
	if (_maxCharsPerLine == 0) {
		_maxCharsPerLine = txt.length();
	}

	SetFontSize(_fontSize);
	MakeMesh();
	_shader = Renderer::instance()->GetShader(2);
	UIText::GetStandardText(this);
}
UIText::~UIText() {
	_vao->Delete();
	_ebo->Delete();
	_vbo->Delete();
	delete[] _verts;
	delete[] _indices;
	delete _vao;
	delete _vbo;
	delete _ebo;
}
void UIText::CenterText(Vec2 size, int vArrSize) {
	size.x *= 0.5f;
	size.y *= 0.5f;
	for (int i = 0; i < vArrSize; i+=5) {//5
		_verts[i] += -size.x;//x
		_verts[i + 1] -= size.y;//x
	}
}
void UIText::SetVert(int charCount, Vec3 pos, char c, GLfloat* verts, Vec2 uvs) {

	verts[charCount] = pos.x;
	charCount++;
	verts[charCount] = pos.y;
	charCount++;
	verts[charCount] = pos.z;
	charCount++;
	//uvs
	verts[charCount] = uvs.x;
	charCount++;
	verts[charCount] = uvs.y;

}
void UIText::SetIndices(int topRight, GLuint* indices, int indexCount) {
	//{2, 1, 0}
	indices[indexCount] = topRight + 2;
	indexCount++;
	indices[indexCount] = topRight + 1;
	indexCount++;
	indices[indexCount] = topRight;
	indexCount++;
	//{2, 3, 1}
	indices[indexCount] = topRight + 2;
	indexCount++;
	indices[indexCount] = topRight + 3;
	indexCount++;
	indices[indexCount] = topRight + 1;
}

//0 top left 1 top right 2 bot left 3 bot right
Vec2 UIText::GetUV(CharData cd, int corner){
	
	Vec2 v = Vec2(cd.x, cd.y);//top left
	if (corner == 0) {//top left
		
	}
	else if (corner == 1) {//top right
		v.x += cd.width;
	}
	else if (corner == 2) {//bot left
		v.y += cd.height;
	}
	else if (corner == 3) {//bot right
	
		v.x += cd.width;
		v.y += cd.height;
	}
	return v;
}

void UIText::BeforeDraw() {
	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "transform"), 1, GL_TRUE, &_transform.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "rotation"), 1, GL_TRUE, &_rotation.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "scale"), 1, GL_TRUE, &_scale.buff[0]);
	Renderer::instance()->SetShaderVariables(_shader);
	Renderer::instance()->GetTexture(_texId)->Bind();
	Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
	glUniform1f(glGetUniformLocation(_shader->ID, "borderWidth"), _borderWidth);
	glUniform2f(glGetUniformLocation(_shader->ID, "offset"), _borderDirection.x, _borderDirection.y);
	glUniform3f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z);
	glUniform3f(glGetUniformLocation(_shader->ID, "outlineColor"), _borderColor.x, _borderColor.y, _borderColor.z);
	_vao->Bind();
}
void UIText::Draw() {
	BeforeDraw();
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
	AfterDraw();
}
void UIText::MakeMesh() {
	int linesTotal = std::ceil(_text.length() / (float)_maxCharsPerLine);

	//set up geometry
	int rowCount = linesTotal * 2;
	int colCount = _maxCharsPerLine * 2;
	int vCount = colCount * rowCount;
	//pos + color + uv
	int vSize = (3 + 2);
	const int vArrSize = vCount * vSize;
	_verts = new GLfloat[vArrSize];

	const int indTotal = 6 * (_maxCharsPerLine * linesTotal);
	_indexCount = indTotal;
	_indices = new GLuint[indTotal];///b5 : 1


	float ySpace = 0.17f;
	Vec3 cursor = Vec3(0, 0, -1);
	Vec2 size = Vec2(-9999, 9999);
	for (int j = 0; j < linesTotal; j++) {
		for (int i = 0; i < _maxCharsPerLine; i++) {
			int charId = i + (j * _maxCharsPerLine);
			char c = ' ';
			if (charId < _text.length()) {
				c = _text[charId];
			}
			//vertex id 
			CharData cd;
			Text::GetCd(c, &cd);

			Vec3 pos = Vec3(cursor.x + cd.xoffset, cursor.y - cd.yoffset, -1);
			SetVert(charId * 4 * vSize, pos, c, _verts, GetUV(cd, 0));//top left			0

			pos.x += cd.width;
			SetVert((charId * 4 + 1) * vSize, pos, c, _verts, GetUV(cd, 1));//top right		1

			pos.x -= cd.width;
			pos.y -= cd.height;
			SetVert((charId * 4 + 2) * vSize, pos, c, _verts, GetUV(cd, 2));//bot left		2

			pos.x += cd.width;
			SetVert((charId * 4 + 3) * vSize, pos, c, _verts, GetUV(cd, 3));//bot right		3


			SetIndices(charId * 4, _indices, charId * 6);
										
			cursor.x += (cd.xadvance - (11.0f/512.0f));//10 is the spacing in the png file and 512 is its size
			//cursor.x += cd.xadvance;//10 is the spacing in the png file and 512 is its size

			if (pos.x > size.x)
				size.x = pos.x;
			if (pos.y < size.y) {
				size.y = pos.y;
			}
		}
		cursor.y -= ySpace;
		cursor.x = 0;
	}
	//size.y = linesTotal * ySpace;
	CenterText(size, vArrSize);
	_vao = new VAO();
	_vao->Bind();

	_vbo = new VBO(_verts, sizeof(_verts) * vArrSize);
	_ebo = new EBO(_indices, sizeof(_indices) * indTotal);
	_vao->LinkAttrib(_vbo, 0, 3, GL_FLOAT, vSize * sizeof(float), (void*)0);//positions
	_vao->LinkAttrib(_vbo, 1, 2, GL_FLOAT, vSize * sizeof(float), (void*)(3 * sizeof(float)));//uvs 
	_vao->Unbind();
	_vbo->Unbind();
	_ebo->Unbind();
}
void UIText::SetFontSize(int size) {
	float baseSize = 50;
	float scaler = 20;
	_fontSize = size;
	_scale.SetScale(Vec3(baseSize + size * scaler, baseSize + size * scaler, 1));
}


void UIText::SetColor(Vec3 col) { _color = col; }
Vec3 UIText::GetColor() { return _color; }
void UIText::SetOutlineColor(Vec3 col) { _borderColor = col; }
Vec3 UIText::GetOutlineColor() { return _borderColor; }
void UIText::SetOutlineWidth(float w) { _borderWidth = w; }
float UIText::GetOutlineWidth() { return _borderWidth; }
void UIText::SetBorderDirection(Vec2 dir) { _borderDirection = dir; }
Vec2 UIText::GetBorderDirection() { return _borderDirection; }

void UIText::GetStandardText(UIText* t) {
	t->SetColor(Vec3(1, 1, 1));
	t->SetOutlineColor(Vec3(0, 0, 0));
	t->SetOutlineWidth(0.6f);
	t->SetBorderDirection(Vec2(0, 0));
}
void UIText::GetDarkText(UIText* t) {
	t->SetColor(Vec3(0.1f, 0.1f, 0.1f));
	t->SetOutlineColor(Vec3(1, 1, 1));
	t->SetOutlineWidth(0.6f);
	t->SetBorderDirection(Vec2(0, 0));
}
void UIText::UpdateModelMatrix(Matrix4x4 parent) {

	/*_model = Matrix4x4::TranslationMatrix(_rect._position) * parent;
	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->UpdateModelMatrix(_model);
	}
	_model = _model * Matrix4x4::RotationMatrix(_rect._angle)
		* Matrix4x4::ScaleMatrix(Vec3(_rect._size.x, _rect._size.y, 1));*/
}