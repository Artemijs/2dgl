#ifndef TOP_DOWN_EDITOR_H
#define TOP_DOWN_EDITOR_H
#include "../../Game/Game.h"
#include "../../Util/MemoryManager.h"


namespace RNT {

	

	class RenderNodeTest : public Game {

	private:
		
	public:
		RenderNodeTest();
		~RenderNodeTest();

		void Update(float deltaTime) override;
		void MoveCamera3D(bool rotate = true, bool move = true);
		void MoveCamera2D();
	};

};

#endif 
