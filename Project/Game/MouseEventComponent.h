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
#endif