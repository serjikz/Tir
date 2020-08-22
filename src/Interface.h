#pragma once
#include "Panel.h"
#include "TextAnimated.h"

class Interface
{
private:	
	Panel::HardPtr _rockets;
	Panel::HardPtr _time;
	Panel::HardPtr _score;
	TextAnimated::HardPtr _tapToPlayText;
public:
	Interface(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
};