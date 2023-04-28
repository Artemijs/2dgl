#ifndef MOUSEEVENTCOMP_H
#define MOUSEEVENTCOMP_H

#include "BaseComponent.h"
#include "../Util/Utility.h"
//#define fptr void(T::* method)()
enum BtnEvent {
	ON_PRESS = 0,
	ON_RELEASE,
	ON_CLICK,
	ON_DOUBLE_CLICK,
	ON_ENTER,
	ON_LEAVE,
	ON_HOVER,
};
template <typename T>class MouseEvent : public BaseComponent {
	
private:
	typedef void(T::* fptr)();
	T* _owner;
	std::vector< std::vector<fptr>*>* _callbacks;
	
	const unsigned int _maxcalls;

public:
	static const unsigned int _id;
	MouseEvent(T* owner): _owner(owner), _maxcalls(6) {
		_callbacks = new std::vector<std::vector<fptr>*>();
		for (int i = 0; i < _maxcalls; i++) {
			_callbacks->push_back(new std::vector<fptr>());
		}
	}
	~MouseEvent() {
		for (int i = 0; i < _maxcalls; i++) {
			delete (_callbacks->at(i));
		}
		delete _callbacks;
	}
	const unsigned int ID() const override {
		return _id;
	}
	void CallEvents(BtnEvent e) {
		auto events = _callbacks->at((int)(e));
		for (int i = 0; i < events->size(); i++) {
			events->at(i)();
		}
	}
	void SetEventCallBack(void(T::* call)(), BtnEvent e) {
		//method = call;
		_callbacks->at((int)(e))->push_back(call);
	}
};
template <class T>
const unsigned int MouseEvent<T>::_id = Utility::GetID();
#endif