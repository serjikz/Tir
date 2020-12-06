#pragma once
#include "BkgObject.h"

class Background
{
private:	
	std::vector<BkgObject::HardPtr> _bkgObjects;
public:
	Background();
	typedef boost::shared_ptr<Background> HardPtr;
	virtual void draw();
	virtual void update(float dt);
};