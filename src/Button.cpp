#include "stdafx.h"
#include "Button.h"

Button::Button(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_t(0.f),
	_state(State::NORMAL),
	_scale(1.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	_speed = Xml::GetIntAttributeOrDef(settings, "speed", 1.f);
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	_speed = Xml::GetFloatAttributeOrDef(settings, "speed", 1.f);
}

void Button::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixScale(_scale, _scale, 1.f);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Button::update(float dt) {
	if (_state == State::OVER) {
		_t += _speed * dt;
		if (_t > 2 * math::PI) {
			_t = 0.f;
		}
		_scale = 1.f + DELTA_SCALE * sinf(_t);
	}
}

void Button::mouseDown(const IPoint& mouse_pos) {
	if (_tex->HitTest(mouse_pos.x + _textureCenter.x - _x, mouse_pos.y + _textureCenter.y - _y)) {
		Message msg = Message("Interface", "SetStateTapToPlay");
		Core::guiManager.getLayer("TestLayer")->getWidget("GameFieldWidget")->AcceptMessage(msg);
	}
}

void Button::mouseMove(const IPoint& mouse_pos) {
	if (_tex->HitTest(mouse_pos.x + _textureCenter.x - _x, mouse_pos.y + _textureCenter.y - _y)) {
		_state = State::OVER;
	}
	else {
		_state = State::NORMAL;
		_scale = 1.f;
		_t = 0.f;
	}
}

void Button::setState(State newState) {
	_state = newState;
}