#pragma once
#include "InterfaceObjectCreator.h"
#include "Panel.h"
#include "InterfaceObject.h"

class PanelCreator : public InterfaceObjectCreator
{
private:
	rapidxml::xml_node<>* _settings;
	
protected:
	virtual InterfaceObject::HardPtr createObject() {
		return InterfaceObject::HardPtr(new Panel(_settings));
	}
public:
	PanelCreator(rapidxml::xml_node<>* settings)
		: _settings(settings)
	{};
	typedef boost::shared_ptr<PanelCreator> HardPtr;
};
