#include "stdafx.h"
#include "RocketsPanel.h"

RocketsPanel::RocketsPanel(rapidxml::xml_node<>* settings, int rocketsAvailable)
	:Panel(settings),
	_text(""),
	_rocketsAvailable(0.f)
{
	_rocketsAvailable = rocketsAvailable;
	_rockets = rocketsAvailable;
	rapidxml::xml_node<>* timeText = settings->first_node("text");
	_textX = Xml::GetIntAttributeOrDef(timeText, "x", 0);
	_textY = Xml::GetIntAttributeOrDef(timeText, "y", 0);
}

void RocketsPanel::draw() {
	if (_state != State::HIDEN) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _splineVal, 0);
		_tex->Draw();
		Render::BindFont("FloralessTime");
		Render::PrintString(_textX, _textY, _text, 1.f, LeftAlign, CenterAlign);
		Render::device.PopMatrix();
	}
}

void RocketsPanel::update(float dt) {
	Panel::update(dt);
	if (_state != State::HIDEN) {
		_text = std::to_string(_rockets);
	}
}

int RocketsPanel::getRocketsCount() {
	return _rockets;
}

void RocketsPanel::decreaseRockets() {
	_rockets--;
	if (_rockets <= 0) {
		Message msg = Message(Message("Interface", "RocketsIsOver"));
		Core::guiManager.getLayer("TestLayer")->getWidget("GameFieldWidget")->AcceptMessage(msg);
		return;
	}
}

void RocketsPanel::setState(Panel::State newState) {
	Panel::setState(newState);
	if (newState == State::APEARENCE) {
		_rockets = _rocketsAvailable;
	}
}