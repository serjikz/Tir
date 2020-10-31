#pragma once

#include "InterfaceObject.h"

class Interface
{
private:	
	InterfaceState _state;
	std::vector<InterfaceObject::HardPtr> _interfaceObjects;
public:
	
	Interface(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
	void setState(InterfaceState newState);
	void setStatisticsMsg(const std::string& msg);
	void mouseMove(const IPoint& mouse_pos);
	void mouseDown(const IPoint& mouse_pos);
	void decreaseRockets();
	int getTime();
	InterfaceState getState();
};