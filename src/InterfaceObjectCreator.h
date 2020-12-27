#pragma once
#include "InterfaceObject.h"

// Фабрика элементов интерфейса
class InterfaceObjectCreator
{
public:
	InterfaceObject::HardPtr createObject(rapidxml::xml_node<>* settings) {
		std::string name = Xml::GetStringAttribute(settings, "name");
		if (name == "missilesPanel") {
			return InterfaceObject::HardPtr(new MissilesPanel(settings));
		}
		else if (name == "timePanel") {
			return InterfaceObject::HardPtr(new TimePanel(settings));
		}
		else if (name == "scorePanel") {
			return InterfaceObject::HardPtr(new ScorePanel(settings));
		}
		else if (name == "arrowHintPanel") {
			return InterfaceObject::HardPtr(new ArrowHintPanel(settings));
		}
		else if (name == "textAnimated") {
			return InterfaceObject::HardPtr(new TextAnimated(settings));
		}
		else {
			assert(false);
		}
	}
	typedef boost::shared_ptr<InterfaceObjectCreator> HardPtr;
};