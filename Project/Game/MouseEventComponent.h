#ifndef MOUSEEVENTCOMP_H
#define MOUSEEVENTCOMP_H
#include <functional>
#include "BaseComponent.h"
#include "../Util/Utility.h"
#include "../Math/Matrix4x4.h"
#define fpointer std::function<void(const Vec3)>
//#define fptr void(T::* method)()
enum class BtnEvent {
	ON_PRESS = 0,
	ON_RELEASE,
	ON_CLICK,
	ON_DOUBLE_CLICK,
	ON_ENTER,
	ON_LEAVE,
	ON_HOVER,
	ON_END_HOVER,
	end
};
class MouseEvent : public BaseComponent {
private:
	std::vector<std::vector<fpointer>*>* _callbacks;
	
public :
	static const unsigned int _component_id;
	MouseEvent();
	~MouseEvent();
	const unsigned int ID() const override;
	void AddEvent(const fpointer &f, const BtnEvent eType);
	void CallEvents(const BtnEvent be, const Vec3 mousepos) const;

};

/*
template <typename T>class MouseEvent : public BaseComponent {
	
private:
	typedef void(T::* fptr)();
	T* _owner;
	std::vector< std::vector<fptr>*>* _callbacks;
	
	const unsigned int _maxcalls;

public:
	static const unsigned int _id;
	MouseEvent(T* owner): _owner(owner), _maxcalls(7) {
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
	void CallEvents(const BtnEvent e) {
		std::vector<fptr>* t = _callbacks->at((int)(e));
		auto events = _callbacks->at((int)(e));
		for (int i = 0; i < events->size(); i++) {
			//fptr func = ;
			(_owner->*events->at(i))();
		}
	}
	void SetEventCallBack(fptr call, const BtnEvent e) {
		//method = call;
		_callbacks->at((int)(e))->push_back(call);
	}
};
template <class T>
const unsigned int MouseEvent<T>::_id = Utility::GetMouseEventID();*/
#endif