#ifndef RENDER_NODE_TEST
#define RENDER_NODE_TEST
#include "../../Game/Game.h"
#include "../../Util/MemoryManager.h"




namespace RNT {

	class RenderNodeTest : public Game {

	private:
		void SetUp();
	public:
		RenderNodeTest();
		~RenderNodeTest();

		void Update(float deltaTime) override;
		void MoveCamera3D(bool rotate = true, bool move = true);
		void MoveCamera2D();
	};

};

#endif 
