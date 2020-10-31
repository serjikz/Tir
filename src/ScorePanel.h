#pragma once
#include "Panel.h"
#include "Button.h"

class ScorePanel : public Panel
{
private:	
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
	virtual void setState(InterfaceState newState);
	void setStatisticsMsg(const std::string &msg);
	void mouseMove(const IPoint& mouse_pos);
	void mouseDown(const IPoint& mouse_pos);
};