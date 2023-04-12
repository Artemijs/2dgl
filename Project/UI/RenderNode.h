#ifndef RENDERNODE_H
#define RENDERNODE_H
#include "../Game/BaseNode.h"
#include "../BackEnd/FBO.h"


class RenderNode : public BaseNode {
private:
	const FBO* _fbo;
public:
	RenderNode();
	RenderNode(Vec3 pos, Vec3 size, float ang);
	~RenderNode();
	void MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) override;
	const FBO* GetFBO() const;
};

#endif
