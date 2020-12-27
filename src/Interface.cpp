#include "stdafx.h"


Interface::Interface()
{
	// Cчитываем эелменты из файла
	rapidxml::xml_node<>* objectSettings = XmlSettings::getInstance()->getGUINode();
	InterfaceObjectCreator::HardPtr objCreator = InterfaceObjectCreator::HardPtr(new InterfaceObjectCreator());
	while (objectSettings) {
		_interfaceObjects.push_back(objCreator->createObject(objectSettings));
		objectSettings = objectSettings->next_sibling();
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
	// Используем посетителя для поиска подходящего обработчика
	ScorePanelMsgVisitor::HardPtr visitor = ScorePanelMsgVisitor::HardPtr(new ScorePanelMsgVisitor(msg));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

void Interface::mouseMove(const IPoint& mouse_pos) {
		// Используем посетителя для поиска подходящего обработчика
	ScorePanelVisitorMouseMove::HardPtr visitor = ScorePanelVisitorMouseMove::HardPtr(new ScorePanelVisitorMouseMove(mouse_pos));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

void Interface::mouseDown(const IPoint& mouse_pos) {
	// Используем посетителя для поиска подходящего обработчика
	ScorePanelVisitorMouseDown::HardPtr visitor = ScorePanelVisitorMouseDown::HardPtr(new ScorePanelVisitorMouseDown(mouse_pos));
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}

int Interface::getTime() {
	// Используем посетителя для поиска подходящего обработчика
	TimePanelVisitor::HardPtr visitor = TimePanelVisitor::HardPtr(new TimePanelVisitor());
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
	return visitor->getTime();
}

void Interface::decreaseMissiles() {
	// Используем посетителя для поиска подходящего обработчика
	MissilesPanelVisitor::HardPtr visitor = MissilesPanelVisitor::HardPtr(new MissilesPanelVisitor());
	for (const auto& intObj : _interfaceObjects) {
		intObj->acceptVisitor(visitor);
	}
}