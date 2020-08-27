#include "stdafx.h"
#include "ArrowHintPanel.h"

ArrowHintPanel::ArrowHintPanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_isMirrored(false),
	_alpha(1.f), 
	_dx(0.f)
{
	_isMirrored = Xml::GetBoolAttributeOrDef(settings, "mirror", false);
}

void ArrowHintPanel::draw() {
	if (_state != State::HIDEN) {
		Render::BeginAlphaMul(_alpha);
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x + _dx, _y, 0);
		if (_isMirrored) {
			Render::device.MatrixScale(-1.f, 1, 1);
		}
		Render::device.MatrixTranslate(-_textureCenter.x, _textureCenter.y, 0);
		_tex->Draw();
		Render::device.PopMatrix();
		Render::EndAlphaMul();
	}
}

void ArrowHintPanel::update(float dt) {
	if (_state != State::HIDEN) {
		_alpha = math::clamp(0.f, 1.f, _alpha + _direction * dt);
		_dx = 1.f + DELTA_POS * sinf(_t);
		_t += _speed * dt;
		if (_t > 2 * math::PI) {
			_t = 0.f;
		}
		if (_alpha < EPS) {
			_state = State::HIDEN;
		}
		if (_isMirrored) {
			_dx *= -1;
		}
	}
}

void ArrowHintPanel::setState(Panel::State newState) {
	Panel::setState(newState);
	if (newState == State::APEARENCE) {
		_t = 0.f;
	}
}