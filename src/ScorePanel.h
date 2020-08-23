#pragma once
#include "Panel.h"

class ScorePanel : public Panel
{
private:	
	FPoint _textureCenter;
	IRect _backSideRect;
public:
	ScorePanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<ScorePanel> HardPtr;
	virtual void draw();
};