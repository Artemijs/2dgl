#include "MouseEvent.h"
#include "MouseEventController.h"
#include "../Util/Callback.h"
using namespace v1_5;
MouseEvent::MouseEvent(Bounds* bounds, BaseObject * bo) {
	_bounds = bounds;
	_baseObject = bo;
	bo->AddCallback(new BBCall(_bounds, bo->GetModelMatrix()));
	MouseEventController::RegisterEvent(this);
}
BaseObject* MouseEvent::GetBaseObject() {
	return _baseObject;
}
void MouseEvent::SetBaseObject(BaseObject* bo) {
	_baseObject = bo;
}
