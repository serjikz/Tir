#pragma once
#include "Panel.h"
#include "Button.h"

class ScorePanel : public Panel
{
private:	
	FPoint _textureCenter;
	IRect _backSideRect;
	float _alphaMiultiplier;
	std::string _text;
	int _textX;
	int _textY;
	Button::HardPtr _restartButton;
public:
	ScorePanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<ScorePanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	void showStatistics(const std::string &msg);
	void mouseMove(const IPoint& mouse_pos);
};