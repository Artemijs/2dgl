#ifndef MOUSEEVENTCOMP_H
#define MOUSEEVENTCOMP_H

#include "BaseComponent.h"
#include "../Util/Utility.h"
template <typename T>class MouseEvent : public BaseComponent {
private:
	T* _owner;
	void(T::* method)();
	static const unsigned int _id;
public:
	MouseEvent(T* owner):_owner(owner) {
	
	}
	~MouseEvent() {
	
	}
	const unsigned int ID() const override {
		return _id;
	}
	void OnPress() {
		(_owner->*method)();
	}
	void SetCallBack(void(T::* call)()) {
		method = call;
	}
};
template <class T>
const unsigned int MouseEvent<T>::_id = Utility::GetID();
#endif