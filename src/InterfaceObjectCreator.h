#pragma once
#include "InterfaceObject.h"

class InterfaceObjectCreator
{
private:
	InterfaceObject::HardPtr _obj;
protected:
	virtual InterfaceObject::HardPtr createObject() = 0;
public:
	InterfaceObjectCreator() {};
	InterfaceObject::HardPtr getObject() {
		if (!_obj) {
			_obj = createObject();
		}
		return _obj;
	};
	typedef boost::shared_ptr<InterfaceObjectCreator> HardPtr;
};