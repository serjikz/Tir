#pragma once
#include "BkgObject.h"

class BkgObjectCreator
{
private:
	BkgObject::HardPtr _obj;
protected:
	virtual BkgObject::HardPtr createObject() = 0;
public:
	BkgObjectCreator() {};
	BkgObject::HardPtr getObject() {
		if (!_obj) {
			_obj = createObject();
		}
		return _obj;
	};
	typedef boost::shared_ptr<BkgObjectCreator> HardPtr;
};