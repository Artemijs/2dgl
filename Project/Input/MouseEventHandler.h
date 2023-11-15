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

	//
	
	/// <summary>
	///	NEEDS TO BE OPTIMISED TO CASH MOUSE EVENT COMPONENT 
	/// HANDLES MOUSE AND UI COLLISION AND EVENTS 
	/// </summary>
	/// <param name="mousePos"></param>
	/// <param name="deltaTime"></param>
	static void HandleMouseMoving(const Vec3 mousePos, const float deltaTime);
	/// <summary>
	/// calls mouse events
	/// </summary>
	/// <param name="on">if the mouse is pressed or resleased</param>
	static void HandleMouseClick(const bool on);
	static void Update(const float deltaTime);
	static void Delete();
	static const Vec3 GetMousePosition();

	static BaseNode* CheckCollision(BaseNode* n, const Vec3 mousePos);
	static void HandleEdgeEvents(BaseNode* node, const Vec3& mousePos);

};
#endif