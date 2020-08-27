#pragma once
#include "Panel.h"
#include <ctime> 

class TimePanel : public Panel
{
private:	
	std::string _text;
	int _timeAvailable;
	int _t0;
	int _textX;
	int _textY;
public:
	TimePanel(rapidxml::xml_node<>* settings, int time);
	typedef boost::shared_ptr<TimePanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(Panel::State newState);
	int getTime();
};