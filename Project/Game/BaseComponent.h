#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include <vector>
	
class BaseComponent{
protected:
	const bool _isGraphic;
public :
	BaseComponent();
	BaseComponent(bool isGraphic);
	virtual ~BaseComponent();
	virtual const unsigned int ID() const = 0;
	const bool IsGraphic() const;
};

#endif


