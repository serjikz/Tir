#pragma once
#include "Panel.h"

class ScorePanel : public Panel
{
private:	
	FPoint _textureCenter;
public:
	ScorePanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<ScorePanel> HardPtr;
	virtual void draw();
};