#include "stdafx.h"
#include "Interface.h"

Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* panel = settings->first_node("Panel");
	_rocketsPanel = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_timePanel = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_scorePanel = ScorePanel::HardPtr(new ScorePanel(panel));
	_tapToPlayText = TextAnimated::HardPtr(new TextAnimated("TAP TO PLAY", Render::device.Width() / 2, Render::device.Height() / 2));
	_state = Interface::State::TAP_TO_PLAY;
}

void Interface::draw() {
	_tapToPlayText->draw();
	_rocketsPanel->draw();
	_timePanel->draw();
	_scorePanel->draw();
	switch (_state) {
		case State::TAP_TO_PLAY: 
			
			break;
		case State::PLAY:
	
			break;
		case State::IS_OVER:
	
			break;
	}
}

void Interface::update(float dt) {
	_tapToPlayText->update(dt);
	_rocketsPanel->update(dt);
	_timePanel->update(dt);
	_scorePanel->update(dt);


	switch (_state) {
	case State::TAP_TO_PLAY:
	
		break;
	case State::PLAY:
	
		break;
	case State::IS_OVER:

		break;
	}
}

void Interface::setState(Interface::State newState) {
	if (newState == State::PLAY) {
		_tapToPlayText->setState(TextAnimated::State::DISSAPEARENCE);
		_timePanel->setState(Panel::State::APEARENCE);
		_rocketsPanel->setState(Panel::State::APEARENCE);
	}
	else if (newState == State::IS_OVER) {
		_timePanel->setState(Panel::State::DISSAPEARENCE);
		_rocketsPanel->setState(Panel::State::DISSAPEARENCE);
		_scorePanel->setState(Panel::State::APEARENCE);
	}
	else if (newState == State::TAP_TO_PLAY) {
		_scorePanel->setState(Panel::State::DISSAPEARENCE);
		_tapToPlayText->setState(TextAnimated::State::APEARENCE);
	}
	_state = newState;
}

Interface::State Interface::getState() {
	return _state;
}