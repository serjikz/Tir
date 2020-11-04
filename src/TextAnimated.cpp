#include "stdafx.h"


TextAnimated::TextAnimated(rapidxml::xml_node<>* settings)
	:_scale(1.f),
	_alpha(1.f)
{
	_t = 0.f;
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	_speed = Xml::GetFloatAttributeOrDef(settings, "speed", 0);
	_deltaScale = Xml::GetFloatAttributeOrDef(settings, "deltaScale", 0);
	_text = Xml::GetStringAttributeOrDef(settings, "text", "");
}

void TextAnimated::draw() {
	if (_alpha > EPS) {
		Render::BindFont("FloralessTap");
		Render::BeginAlphaMul(_alpha);
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _y, 0);
		Render::device.MatrixScale(_scale, _scale, 1.f);
		Render::device.MatrixTranslate(-Render::device.Width() / 2.f, -Render::device.Height() / 2.f, 0);
		Render::PrintString(_x, _y, _text, 1.f, CenterAlign, BottomAlign);
		Render::device.PopMatrix();
		Render::EndAlphaMul();
	}
}

void TextAnimated::update(float dt) {
	_t += _speed * dt;
	if (_t > 2 * math::PI) {
		_t = 0.f;
	}
	_scale = 1.f + _deltaScale * sinf(_t);
	_alpha = math::clamp(0.f, 1.f, _alpha + _direction * dt);
}

void TextAnimated::setState(InterfaceState newState){
	if (newState == InterfaceState::PLAY) {
		_state = State::DISSAPEARENCE;
		_direction = -1.f;
	}else if (newState == InterfaceState::TAP_TO_PLAY) {
		_state = State::APEARENCE;
		_direction = 1.f;
		_t = 0.f;
	}
}