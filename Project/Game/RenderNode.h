#ifndef RENDERNODE_H
#define RENDERNODE_H
#include "./BaseNode.h"
#include "../Game/FBOComponent.h"




class RenderNode : public BaseNode {
private:

	FBOComponent* _fboComp;
	BaseMaterial* _nodeMat;
	void AddFBO() ;
public:
	RenderNode();
	RenderNode(const Vec3 pos, const Vec3 size, const float ang);
	
	~RenderNode();
	void MakeModelMatrix(const Matrix4x4 trans, const Matrix4x4 scale, const Matrix4x4 rot) override;
	const FBOComponent* GetFBOComp() const;
	void SetNodeMat(BaseMaterial* bm);
	BaseMaterial* GetMaterial()const ;

};
#endif