#pragma once
#include "Panel.h"
#include <ctime> 

class MissilesPanel : public Panel
{
private:	
	std::string _text;
	int _missilesAvailable;
	int _missiles;
	int _t0;
	int _textX;
	int _textY;
public:
	MissilesPanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<MissilesPanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(InterfaceState newState);
	void decreaseRockets();
	int getRocketsCount();
};