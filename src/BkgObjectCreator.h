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
	BkgObject::HardPtr getObject();
	typedef boost::shared_ptr<BkgObjectCreator> HardPtr;
};