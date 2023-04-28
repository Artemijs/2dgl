#ifndef MOUSE_EVENT_HANDLER_H
#define MOUSE_EVENT_HANDLER_H
#include "../Game/BaseNode.h"
//#include "MouseEvent.h"
#include <vector>
class MouseEventHandler {
private:
	//static std::vector<MouseEvent*>* _all_events;
	static BaseNode* _current;
	static float _time;
	static float _hover_time;
	static Vec2* _prevPos;
	static bool _onHover;
	static bool _on;
	static float _ddclick_time;
	static float _dd_time_max;
public:

	//static void RegisterEvent(MouseEvent* m);
	static void HandleMouseMoving(const Vec2 mousePos, const float deltaTime);
	static void HandleMouseClick(const bool on);
	static void Update(const float deltaTime);
	static void Delete();
	static const Vec2* GetMousePosition();

	static BaseNode* CheckCollision(const BaseNode* n, const Vec2 mousePos);

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