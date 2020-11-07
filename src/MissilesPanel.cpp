#include "stdafx.h"


MissilesPanel::MissilesPanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_text(""),
	_missilesAvailable(0.f)
{
	rapidxml::xml_node<>* timeText = settings->first_node("text");
	_textX = Xml::GetIntAttributeOrDef(timeText, "x", 0);
	_textY = Xml::GetIntAttributeOrDef(timeText, "y", 0);
	std::string params;
	std::ifstream in("input.txt");
	std::string paramToFound = "Missiles=";
	if (in.is_open())
	{
		while (getline(in, params)) {
			if (params.substr(0, std::string(paramToFound).length()) == paramToFound) {
				_missilesAvailable = stoi(params.substr(paramToFound.length(), params.length() - 1));
			}
		}
	}
	in.close();

}

void MissilesPanel::draw() {
	if (_state != State::HIDEN) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _splineVal, 0);
		_tex->Draw();
		Render::BindFont("FloralessTime");
		Render::PrintString(_textX, _textY, _text, 1.f, LeftAlign, CenterAlign);
		Render::device.PopMatrix();
	}
}

void MissilesPanel::update(float dt) {
	Panel::update(dt);
	if (_state != State::HIDEN) {
		_text = std::to_string(math::clamp(0, _missilesAvailable, _missiles));
	}
}

int MissilesPanel::getRocketsCount() {
	return _missiles;
}

void MissilesPanel::decreaseMissiles() {
	_missiles--;
}

void MissilesPanel::setState(InterfaceState newState) {
	if (newState == InterfaceState::PLAY) {
		_missiles = _missilesAvailable;
		Panel::setState(State::APEARENCE);
	}
	else if (newState == InterfaceState::IS_OVER) {
		Panel::setState(State::DISSAPEARENCE);
	}
}

void MissilesPanel::acceptVisitor(InterfaceObjVisitor::HardPtr visitor) {
	visitor->visitMissilesPanel(this);
}