#pragma once

#include "InterfaceObject.h"

// Пользовательский интерфейс
class Interface
{
private:	
	InterfaceState _state;
	std::vector<InterfaceObject::HardPtr> _interfaceObjects;
public:
	
	Interface();
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
	void setState(InterfaceState newState);
	void setStatisticsMsg(const std::string& msg);
	void mouseMove(const IPoint& mouse_pos);
	void mouseDown(const IPoint& mouse_pos);
	void decreaseMissiles();
	int getTime();
	InterfaceState getState();
};