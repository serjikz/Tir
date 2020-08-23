#include "stdafx.h"
#include "Panel.h"

Panel::Panel(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_t(0.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	_speed = Xml::GetIntAttributeOrDef(settings, "speed", 1.f);
	rapidxml::xml_node<>* splinePoints = settings->first_node("spline");
	while (splinePoints) {
		float t = Xml::GetFloatAttributeOrDef(splinePoints, "t", 0.f);
		float y = Xml::GetFloatAttributeOrDef(splinePoints, "y", 0.f);
		_spline.addKey(t, y);
		splinePoints = splinePoints->next_sibling();
	}
	_spline.CalculateGradient();
}

void Panel::draw() {
	if (_state != State::HIDEN) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _y, 0);
		_tex->Draw();
		Render::device.PopMatrix();
	}
}

void Panel::update(float dt) {
	if (_state != State::HIDEN) {
		_t = math::clamp(0.f, 1.f, _t + _speed * dt);
		_y = _spline.getGlobalFrame(_t);
	}
}

void Panel::setState(Panel::State newState) {
	_state = newState;
}