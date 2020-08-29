#pragma once
#include "Panel.h"
#include <ctime> 

class RocketsPanel : public Panel
{
private:	
	std::string _text;
	int _rocketsAvailable;
	int _rockets;
	int _t0;
	int _textX;
	int _textY;
public:
	RocketsPanel(rapidxml::xml_node<>* settings, int rocketsAvailable);
	typedef boost::shared_ptr<RocketsPanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(Panel::State newState);
	void decreaseRockets();
	int getRocketsCount();
};