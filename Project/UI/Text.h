#ifndef TEXT_H
#define TEXT_H

#include "../Graphics/Graphic.h"
#include <vector>
#include "../BackEnd/VAO.h"
#include "../BackEnd/VBO.h"
#include "../BackEnd/EBO.h"
#include "../Math/Matrix4x4.h"
#include "../Graphics/Materials/MaterialText.h"
//char id=32 x=0 y=0 width=0 height=0 xoffset=1 yoffset=1 xadvance=43 page=0 chnl=15
struct CharData {
	int id;
	float x;
	float y;
	float width;
	float height;
	float xoffset;
	float yoffset;
	float xadvance;

};

class Text : public Graphic {
private:
	static  std::vector<CharData>* _allData;
	const VAO* _vao;
	VBO* _vbo;
	EBO* _ebo;
	GLfloat* _verts;
	GLuint* _indices;

	int _maxCharsPerLine;
	//int _indexCount;
	int _fontSize;
	std::string _text;
	MaterialText* _material;
	Vec2 GetUV(CharData cd, int corner);
	void SetVert(int charCount, Vec3 pos, char c, GLfloat* verts, Vec2 uvs);
	void SetIndices(int topRight, GLuint* indices, int indexCount);

	void MakeMesh();
	void CenterText(Vec2 size, int vArrSize);
public:
	static const unsigned int _component_id;
	Text( std::string txt, int fontSize = 6, int maxCharPerLine = 0);
	~Text();
	static void Init();
	static void GetCd(char c, CharData* cd);
	const Texture* GetTexture();
	//void BeforeDraw();
	//void Draw();
	void SetFontSize(int size);
	int GetFontSize() { return _fontSize; }
	const VAO* GetVAO() { return _vao; }
	std::string GetText() { return _text; }

	/*void SetSize(Vec2 size);
	void SetPosition(Vec3 pos);
	void SetAngle(float angle);
	*/
	void SetColor(const Vec3 col);
	const Vec3 GetColor();
	void SetOutlineColor(const Vec3 col);
	const Vec3 GetOutlineColor();
	void SetOutlineWidth(const float w);
	float GetOutlineWidth();
	void SetBorderDirection(const Vec2 dir);
	const Vec2 GetBorderDirection();
	void SetText(std::string txt) {
		_text = txt;
		std::cout << "USED SET TEXT, SET TEXT NOT IMPLEMENTED\n";
	}
	int GetMaxPerLine() {
		return _maxCharsPerLine;
	}
	int GetIndexCount() {
		return _indexCount;
	}
	static void GetStandardText(Text* t);
	static void GetDarkText(Text* t);
	const unsigned int ID() const override;
};


#endif // !TEXT_H