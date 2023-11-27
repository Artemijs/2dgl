#ifndef RENDER_NODE_TEST
#define RENDER_NODE_TEST
#include "../../Game/Game.h"
#include "../../Util/MemoryManager.h"
#include "../../Graphics/Renderer.h"



namespace RNT {

	class RenderNodeTest : public Game {

	private:
		void SetUp();
		void SetUpB();
		void ButtonInNode();
		RenderNode* _rn1;
		Vec3 _fboSize;
		Vec3 _fboPos;
		Vec3 _imgPos;
		Vec3 _imgSize;
	public:
		RenderNodeTest();
		~RenderNodeTest();

		void Update(float deltaTime) override;
		void MoveCamera3D(bool rotate = true, bool move = true);
		void MoveCamera2D();
	};

};

#endif 
