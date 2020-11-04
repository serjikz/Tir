#include "stdafx.h"


Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* objSettings = settings->first_node("InterfaceObject");
	InterfaceObjectCreator::HardPtr objCreator = InterfaceObjectCreator::HardPtr(new InterfaceObjectCreator());
	while (objSettings) {
		_interfaceObjects.push_back(objCreator->createObject(objSettings));
		objSettings = objSettings->next_sibling();
	}
	_state = InterfaceState::TAP_TO_PLAY;
}

void Interface::draw() {
	for (const auto& intObj : _interfaceObjects) {
		intObj->draw();
	}
}

void Interface::update(float dt) {
	for (const auto& intObj : _interfaceObjects) {
		intObj->update(dt); 
	}
}

void Interface::setState(InterfaceState newState) {
	for (const auto& intObj : _interfaceObjects) {
		intObj->setState(newState);
	}
	_state = newState;
}

InterfaceState Interface::getState() {
	return _state;
}

void Interface::setStatisticsMsg(const std::string& msg) {
	/*ScorePanelVisitor::HardPtr visitor = ScorePanelVisitor::HardPtr(new ScorePanelVisitor(msg));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}*/
}

void Interface::mouseMove(const IPoint& mouse_pos) {
//_scorePanel->mouseMove(mouse_pos);
}

void Interface::mouseDown(const IPoint& mouse_pos) {
	//_scorePanel->mouseDown(mouse_pos);
}

int Interface::getTime() {
	//return _timePanel->getTime();
	return 100;
}

void Interface::decreaseRockets() {
	//_rocketsPanel->decreaseRockets();
}