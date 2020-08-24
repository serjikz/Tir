#pragma once
#include "Panel.h"

class TimePanel : public Panel
{
private:	
	FPoint _textureCenter;
	IRect _backSideRect;
	float _alphaMiultiplier;
public:
	TimePanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<TimePanel> HardPtr;
	virtual void draw();
};