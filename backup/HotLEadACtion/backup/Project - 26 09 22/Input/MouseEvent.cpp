#include "MouseEvent.h"
#include "MouseEventController.h"

MouseEvent::MouseEvent(Bounds* bounds) {
	_bounds = bounds;
	MouseEventController::RegisterEvent(this);
}
