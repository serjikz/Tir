#pragma once
#include "Panel.h"
#include "ScorePanel.h"
#include "TimePanel.h"
#include "TextAnimated.h"
#include "ArrowHintPanel.h"
#include "MissilesPanel.h"
#include "InterfaceConcreteCreators.h"

class Interface
{
private:	
	MissilesPanel::HardPtr _rocketsPanel;
	TimePanel::HardPtr _timePanel;
	ScorePanel::HardPtr _scorePanel;
	TextAnimated::HardPtr _tapToPlayText;
	ArrowHintPanel::HardPtr _leftArrowHintPanel;
	ArrowHintPanel::HardPtr _rightArrowHintPanel;
public:
	enum class State {
		TAP_TO_PLAY,
		PLAY,
		IS_OVER
	} _state;
	Interface(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Interface> HardPtr;
	void draw();
	void update(float dt);
	void setState(Interface::State newState);
	void setStatisticsMsg(const std::string& msg);
	void mouseMove(const IPoint& mouse_pos);
	void mouseDown(const IPoint& mouse_pos);
	void decreaseRockets();
	int getTime();
	State getState();
};