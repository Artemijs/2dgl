#include "Callback.h"

BBCall::BBCall(Bounds* b, Matrix4x4* m) {
	_bounds = b;
	_model = m;
}
void BBCall::Execute() {
	//_bounds->Translate2World((*_model));
}
