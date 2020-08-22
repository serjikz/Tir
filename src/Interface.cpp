#include "stdafx.h"
#include "Interface.h"

Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* panel = settings->first_node("Panel");
	_rocketsPanel = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_timePanel = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_scorePanel = Panel::HardPtr(new Panel(panel));
	_tapToPlayText = TextAnimated::HardPtr(new TextAnimated("TAP TO PLAY", Render::device.Width() / 2, Render::device.Height() / 2));
	_state = Interface::State::TAP_TO_PLAY;
}

void Interface::draw() {
	switch (_state) {
		case State::TAP_TO_PLAY: 
			_tapToPlayText->draw();
			break;
		case State::PLAY:
			_rocketsPanel->draw();
			_timePanel->draw();
			break;
		case State::IS_OVER:
			_scorePanel->draw();
			break;
	}
}

void Interface::update(float dt) {
	switch (_state) {
	case State::TAP_TO_PLAY:
		_tapToPlayText->update(dt);
		break;
	case State::PLAY:
		_rocketsPanel->update(dt);
		_timePanel->update(dt);
		break;
	case State::IS_OVER:
		_scorePanel->update(dt);
		break;
	}
}

void Interface::setState(Interface::State state) {
	_state = state;
}

Interface::State Interface::getState() {
	return _state;
}