#include "stdafx.h"


Panel::Panel(rapidxml::xml_node<>* settings)
	: _t(0.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	_speed = Xml::GetIntAttributeOrDef(settings, "speed", 1.f);
	rapidxml::xml_node<>* splinePoints = settings->first_node("spline");
	while (splinePoints) {
		float t = Xml::GetFloatAttributeOrDef(splinePoints, "t", 0.f);
		float value = Xml::GetFloatAttributeOrDef(splinePoints, "value", 0.f);
		_spline.addKey(t, value);
		splinePoints = splinePoints->next_sibling();
	}
	if (!_spline.empty()) {
		_spline.CalculateGradient();
	}
}

void Panel::draw() {
	if (_state != State::HIDEN) {
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _splineVal, 0);
		_tex->Draw();
		Render::device.PopMatrix();
	}
}

void Panel::update(float dt) {
	if (_state != State::HIDEN) {
		_t = math::clamp(0.f, 1.f, _t + _speed * _direction * dt);
		_splineVal = _spline.getGlobalFrame(_t);
		if (_t < EPS) {
			_state = State::HIDEN;
		}
	}
}

void Panel::setState(InterfaceObject::State newState) {
	_state = newState;
	if (newState == InterfaceObject::State::APEARENCE) {
		_direction = 1.f;
	}
	else if (newState == InterfaceObject::State::DISSAPEARENCE) {
		_direction = -1.f;
	}
}