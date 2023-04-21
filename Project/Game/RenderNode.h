#ifndef RENDERNODE_H
#define RENDERNODE_H
#include "./BaseNode.h"
//#include "../BackEnd/FBO.h"
class RenderNode : public BaseNode {
private:
	//const FBO _fbo;
public:
	RenderNode();
	RenderNode(const Vec3 pos, const Vec3 size, const float ang);
	~RenderNode();
	void MakeModelMatrix(const Matrix4x4 trans, const Matrix4x4 scale, const Matrix4x4 rot) override;
	//const FBO GetFBO() const;

};
#endif