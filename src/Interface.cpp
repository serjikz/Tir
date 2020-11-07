#include "stdafx.h"


Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* objSettings = settings->first_node("InterfaceObject");
	InterfaceObjectCreator::HardPtr objCreator = InterfaceObjectCreator::HardPtr(new InterfaceObjectCreator());
	while (objSettings) {
		_interfaceObjects.push_back(objCreator->createObject(objSettings));
		objSettings = objSettings->next_sibling();
	}
	setState(InterfaceState::TAP_TO_PLAY);
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
	ScorePanelMsgVisitor::HardPtr visitor = ScorePanelMsgVisitor::HardPtr(new ScorePanelMsgVisitor(msg));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

void Interface::mouseMove(const IPoint& mouse_pos) {
	ScorePanelVisitorMouseMove::HardPtr visitor = ScorePanelVisitorMouseMove::HardPtr(new ScorePanelVisitorMouseMove(mouse_pos));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

void Interface::mouseDown(const IPoint& mouse_pos) {
	ScorePanelVisitorMouseDown::HardPtr visitor = ScorePanelVisitorMouseDown::HardPtr(new ScorePanelVisitorMouseDown(mouse_pos));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

int Interface::getTime() {
	TimePanelVisitor::HardPtr visitor = TimePanelVisitor::HardPtr(new TimePanelVisitor());
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
	return visitor->getTime();
}

void Interface::decreaseMissiles() {
	MissilesPanelVisitor::HardPtr visitor = MissilesPanelVisitor::HardPtr(new MissilesPanelVisitor());
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}