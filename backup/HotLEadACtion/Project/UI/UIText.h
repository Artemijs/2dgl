#ifndef UITEXT_H
#define UITEXT_H
#include "../Graphics/Texture.h"
#include "../Graphics/Graphic.h"
#include <vector>
#include "../BackEnd/VAO.h"
#include "../BackEnd/VBO.h"
#include "../BackEnd/EBO.h"
#include "../Math/Matrix4x4.h"
#include "Element.h"
#include "../Graphics/Text.h"
class UIText : public Graphic, public Element {
private:
	VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;
	GLfloat* _verts;
	GLuint* _indices;

	int _maxCharsPerLine;
	int _indexCount;
	int _fontSize;
	std::string _text;
	Vec2 _borderDirection;
	float _borderWidth;
	Vec3 _color;
	Vec3 _borderColor;

	Vec2 GetUV(CharData cd, int corner);
	void SetVert(int charCount, Vec3 pos, char c, GLfloat* verts, Vec2 uvs);
	void SetIndices(int topRight, GLuint* indices, int indexCount);
	void MakeMesh();
	void CenterText(Vec2 size, int vArrSize);
public :
	UIText(Vec3 pos, float angle, int fontSize, std::string txt, int maxCharPerLine = 0);
	~UIText();
	void BeforeDraw();
	void Draw();
	void UpdateModelMatrix(Matrix4x4 parent);
	void SetFontSize(int size);
	int GetFontSize() { return _fontSize; }
	VAO* GetVAO() { return _vao; }
	std::string GetText() { return _text; }
	/*void SetSize(Vec2 size);
	void SetPosition(Vec3 pos);
	void SetAngle(float angle);
	*/
	void SetColor(Vec3 col);
	Vec3 GetColor();
	void SetOutlineColor(Vec3 col);
	Vec3 GetOutlineColor();
	void SetOutlineWidth(float w);
	float GetOutlineWidth();
	void SetBorderDirection(Vec2 dir);
	Vec2 GetBorderDirection();
	void SetText(std::string txt) {
		_text = txt;
	}
	int GetMaxPerLine() {
		return _maxCharsPerLine;
	}
	int GetIndexCount() {
		return _indexCount;
	}
	static void GetStandardText(UIText* t);
	static void GetDarkText(UIText* t);
};


#endif // !TEXT_H
