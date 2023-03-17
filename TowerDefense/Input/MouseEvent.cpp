#include "MouseEvent.h"
#include "MouseEventController.h"
#include "../Util/Callback.h"
MouseEvent::MouseEvent(Bounds* bounds, BaseObject * bo) {
	_bounds = bounds;
	bo->AddCallback(new BBCall(_bounds, bo->GetModelMatrix()));
	MouseEventController::RegisterEvent(this);
}
