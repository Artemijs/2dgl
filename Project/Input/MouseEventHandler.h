#ifndef MOUSE_EVENT_HANDLER_H
#define MOUSE_EVENT_HANDLER_H
#include "../Game/BaseNode.h"
#include "../Game/MouseEventComponent.h"
#include <vector>
class MouseEventHandler {
private:
	static BaseNode* _current;
	static MouseEvent* _current_m;
	static float _time;
	static float _hover_time;
	static Vec3 _prevPos;
	static bool _onHover;
	static bool _on;
	static float _ddclick_time;
	static float _dd_time_max;
public:

	//NEEDS TO BE OPTIMISED TO CASH MOUSE EVENT COMPONENT
	static void HandleMouseMoving(const Vec3 mousePos, const float deltaTime);
	static void HandleMouseClick(const bool on);
	static void Update(const float deltaTime);
	static void Delete();
	static const Vec3 GetMousePosition();

	static BaseNode* CheckCollision(BaseNode* n, const Vec3 mousePos);

	/*
	A RECURSIVE COLLISION CHECK
	has to return closest to the camera object that intersects with mouse
	
	//COLLISION DETECTION
	const BaseNode* CheckCollision(node n, Vec2 mousePos) const{
		const Bounds* bb = n->GetComponent<Bounds>();
		auto children = n->GetChildren();
		BaseNode* closest_n = NULL;

		if( children !=NULL){
			for(int i =0; i < n->children->size(); ++i){
		
				const BaseNode* bn = CheckCollision (childre->at(i), mousePos);

				if(bn == null) continue;

				if(closest_n == NULL)
					closest_n = bn;
				else{
				//buf[11] is the world space z value
					if(bn->_model->buff[11]> closest_n->_model->buff[11])
						closest_n = bn;
				}
			}
		}
		if(bb != null){

			if(closest_n == NULL)	return n;

			else if (bb->CheckInside(mousePos)){
				if(n->_model->buff[11]> closest_n->_model->buff[11]){
					closest_n = n;
				}
			}
		}
		return closest_n;
	}

	*/

};
#endif