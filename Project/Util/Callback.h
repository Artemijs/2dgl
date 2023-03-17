#ifndef CALLBACK_H
#define CALLBACK_H
#include "../Math/Bounds.h"
class BaseCall {
public:
	virtual void Execute() = 0;
};

class BBCall: public BaseCall{
public :
	Bounds* _bounds;
	Matrix4x4* _model;
	BBCall(Bounds* b, Matrix4x4* m);
	void Execute();
};
#endif