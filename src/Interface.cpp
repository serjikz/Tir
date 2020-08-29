#include "stdafx.h"
#include "Interface.h"

Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* panel = settings->first_node("Panel");
	_rocketsPanel = RocketsPanel::HardPtr(new RocketsPanel(panel, Xml::GetIntAttributeOrDef(settings, "rockets", 0)));
	panel = panel->next_sibling();
	_timePanel = TimePanel::HardPtr(new TimePanel(panel, Xml::GetIntAttributeOrDef(settings, "time", 0)));
	panel = panel->next_sibling();
	_scorePanel = ScorePanel::HardPtr(new ScorePanel(panel));
	panel = panel->next_sibling();
	_leftArrowHintPanel = ArrowHintPanel::HardPtr(new ArrowHintPanel(panel));
	panel = panel->next_sibling();
	_rightArrowHintPanel = ArrowHintPanel::HardPtr(new ArrowHintPanel(panel));
	_tapToPlayText = TextAnimated::HardPtr(new TextAnimated("TAP TO PLAY", Render::device.Width() / 2, Render::device.Height() / 2));
	_state = Interface::State::TAP_TO_PLAY;
}

void Interface::draw() {
	_tapToPlayText->draw();
	_rocketsPanel->draw();
	_timePanel->draw();
	_scorePanel->draw();
	_leftArrowHintPanel->draw();
	_rightArrowHintPanel->draw();
}

void Interface::update(float dt) {
	_tapToPlayText->update(dt);
	_rocketsPanel->update(dt);
	_timePanel->update(dt);
	_scorePanel->update(dt);
	_leftArrowHintPanel->update(dt);
	_rightArrowHintPanel->update(dt);
}

void Interface::setState(Interface::State newState) {
	if (newState == State::PLAY) {
		_tapToPlayText->setState(TextAnimated::State::DISSAPEARENCE);
		_timePanel->setState(Panel::State::APEARENCE);
		_rocketsPanel->setState(Panel::State::APEARENCE);
		_leftArrowHintPanel->setState(Panel::State::DISSAPEARENCE);
		_rightArrowHintPanel->setState(Panel::State::DISSAPEARENCE);
	}
	else if (newState == State::IS_OVER) {
		_timePanel->setState(Panel::State::DISSAPEARENCE);
		_rocketsPanel->setState(Panel::State::DISSAPEARENCE);
		_scorePanel->setState(Panel::State::APEARENCE);
	}
	else if (newState == State::TAP_TO_PLAY) {
		_scorePanel->setState(Panel::State::DISSAPEARENCE);
		_tapToPlayText->setState(TextAnimated::State::APEARENCE);
		_leftArrowHintPanel->setState(Panel::State::APEARENCE);
		_rightArrowHintPanel->setState(Panel::State::APEARENCE);
	}
	_state = newState;
}

Interface::State Interface::getState() {
	return _state;
}

void Interface::setStatisticsMsg(const std::string& msg) {
	_scorePanel->setStatisticsMsg(msg);
}

void Interface::mouseMove(const IPoint& mouse_pos) {
	_scorePanel->mouseMove(mouse_pos);
}

void Interface::mouseDown(const IPoint& mouse_pos) {
	_scorePanel->mouseDown(mouse_pos);
}

int Interface::getTime() {
	return _timePanel->getTime();
}

void Interface::decreaseRockets() {
	_rocketsPanel->decreaseRockets();
}