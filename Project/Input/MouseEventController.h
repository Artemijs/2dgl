#ifndef MOUSE_EVENT_CONTROLLER_H
#define MOUSE_EVENT_CONTROLLER_H

#include "MouseEvent.h"
#include <vector>
class MouseEventController {
private:
	static std::vector<MouseEvent*>* _all_events;
	static MouseEvent* _current;
	static float _time;
	static float _hover_time;
	static Vec2* _prevPos;
	static bool _onHover;
	static bool _on;
	static float _ddclick_time;
	static float _dd_time_max;
	static std::vector<unsigned int>* _partitions;
	static int _bpi; //bits per int
public:
	
	static void RegisterEvent(MouseEvent* m);
	static void HandleMouseMoving(const Vec2 mousePos, const float deltaTime);
	static void HandleMouseClick(const bool on);
	static void Update(const float deltaTime);
	static void Delete();
	static const Vec2* GetMousePosition();


	

};
#endif
