#pragma once
#include "BkgObjectCreator.h"
#include "BackgroundPicture.h"
#include "Cloud.h"

class PanelCreator : public ObjectCreator
{
private:
	rapidxml::xml_node<>* _settings;
	
protected:
	virtual BkgObject::HardPtr createObject() {
		return BkgObject::HardPtr(new Cloud(_settings));
	}
public:
	CloudCreator(rapidxml::xml_node<>* settings) 
		: _settings(settings)
	{};
	typedef boost::shared_ptr<CloudCreator> HardPtr;
};
