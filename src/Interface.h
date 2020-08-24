#pragma once
#include "Panel.h"
#include "ScorePanel.h"
#include "TimePanel.h"
#include "TextAnimated.h"

class Interface
{
private:	
	Panel::HardPtr _rocketsPanel;
	TimePanel::HardPtr _timePanel;
	ScorePanel::HardPtr _scorePanel;
	TextAnimated::HardPtr _tapToPlayText;
public:
	enum class State {
		TAP_TO_PLAY,
		PLAY,
		IS_OVER
	} _state;
	Interface(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
	void setState(Interface::State newState);
	State getState();
};