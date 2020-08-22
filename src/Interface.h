#pragma once
#include "Panel.h"
#include "TextAnimated.h"

class Interface
{
private:	
	enum State {
		TAP_TO_PLAY,
		PLAY,
		IS_OVER
	} _state;
	Panel::HardPtr _rocketsPanel;
	Panel::HardPtr _timePanel;
	Panel::HardPtr _scorePanel;
	TextAnimated::HardPtr _tapToPlayText;
public:
	Interface(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
};