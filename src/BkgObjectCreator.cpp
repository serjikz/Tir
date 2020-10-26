#include "stdafx.h"
#include "BkgObjectCreator.h"


BkgObject::HardPtr BkgObjectCreator::getObject() {
	if (!_obj) {
		_obj = createObject();
	}
	return _obj;
};