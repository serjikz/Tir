#pragma once
#include "Panel.h"
#include <ctime> 

// Панель таймера 
class TimePanel : public Panel
{
private:	
	std::string _text;
	size_t _timeAvailable;
	size_t _t0;
	int _textX;
	int _textY;
public:
	TimePanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<TimePanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(InterfaceState newState);
	virtual void acceptVisitor(InterfaceObjVisitor::HardPtr visitor);
	int getTime();
};