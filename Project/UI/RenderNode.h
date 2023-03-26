#ifndef RENDERNODE_H
#define RENDERNODE_H
#include "../Game/BaseObject.h"
class RenderNode : public BaseObject{
private:
	
public :
	RenderNode();
	RenderNode(Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);
	void MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) override;
};
#endif
