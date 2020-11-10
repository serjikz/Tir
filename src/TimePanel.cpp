#include "stdafx.h"


TimePanel::TimePanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_text(""),
	_timeAvailable(0),
	_t0(0)
{
	rapidxml::xml_node<>* timeText = settings->first_node("text");
	_textX = Xml::GetIntAttributeOrDef(timeText, "x", 0);
	_textY = Xml::GetIntAttributeOrDef(timeText, "y", 0);
	_timeAvailable = InputFileReader::getInstance()->getGameTime();
}

void TimePanel::draw() {
	if (_state != State::HIDEN) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _splineVal, 0);
		_tex->Draw();
		Render::BindFont("FloralessTime");
		Render::PrintString(_textX, _textY, _text, 1.f, LeftAlign, CenterAlign);
		Render::device.PopMatrix();
	}
}

void TimePanel::update(float dt) {
	Panel::update(dt);
	if (_state != State::HIDEN) {
		size_t t = _timeAvailable - (clock() - _t0) / 1000;
		if (t <= 0 && _state != State::DISSAPEARENCE) {
			Message msg = Message(Message("ShowStats", "TimeIsOver"));
			Core::guiManager.getLayer("TestLayer")->getWidget("GameFieldWidget")->AcceptMessage(msg);
			return;
		}
		size_t min = t / 60;
		size_t sec = t % 60;
		std::string m = std::to_string(min);
		std::string s = std::to_string(sec);
		if (min < 10) {
			m = "0" + m;
		}
		if (sec < 10) {
			s = "0" + s;
		}
		_text = m + ":" + s;
	}
}

int TimePanel::getTime() {
	return _timeAvailable;
}

void TimePanel::setState(InterfaceState newState) {
	if (newState == InterfaceState::PLAY) {
		Panel::setState(State::APEARENCE);
		_t0 = (size_t) clock();
	}
	else if (newState == InterfaceState::IS_OVER) {
		Panel::setState(State::DISSAPEARENCE);
	}
}

void TimePanel::acceptVisitor(InterfaceObjVisitor::HardPtr visitor) {
	visitor->visitTimePanel(this);
}