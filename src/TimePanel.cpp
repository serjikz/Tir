#include "stdafx.h"
#include "TimePanel.h"

TimePanel::TimePanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_text(""),
	_timeAvailable(0.f),
	_t0(0)
{
	_timeAvailable = Xml::GetFloatAttributeOrDef(settings, "time", 0.f);
	rapidxml::xml_node<>* timeText = settings->first_node("text");
	_textX = Xml::GetIntAttributeOrDef(timeText, "x", 0);
	_textY = Xml::GetIntAttributeOrDef(timeText, "y", 0);
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
		int t = _timeAvailable - (clock() - _t0) / 1000;
		int min = t / 60;
		int sec = t % 60;
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

void TimePanel::setState(Panel::State newState) {
	Panel::setState(newState);
	if (newState == State::APEARENCE) {
		_t0 = clock();
	}
	else if (newState == State::DISSAPEARENCE) {

	}
}