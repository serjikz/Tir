#include "stdafx.h"
#include "Interface.h"
#include "ScorePanel.h"
#include "TimePanel.h"
#include "TextAnimated.h"
#include "ArrowHintPanel.h"
#include "MissilesPanel.h"
#include "InterfaceObjectCreator.h"

Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* panel = settings->first_node("Panel");
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new MissilesPanel(panel)));
	panel = panel->next_sibling();
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new TimePanel(panel)));
	panel = panel->next_sibling();
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new ScorePanel(panel)));
	panel = panel->next_sibling();
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new ArrowHintPanel(panel)));
	panel = panel->next_sibling();
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new ArrowHintPanel(panel)));
	_interfaceObjects.push_back(InterfaceObject::HardPtr(new TextAnimated("TAP TO PLAY", 
								Render::device.Width() / 2, Render::device.Height() / 2)));

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
	//_scorePanel->setStatisticsMsg(msg);
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