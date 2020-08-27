#include "stdafx.h"
#include "TextAnimated.h"

TextAnimated::TextAnimated(const std::string& text, int x, int y)
	:_x(x),
	_y(y),
	_text(text),
	_scale(1.f),
	_t(0.f),
	_alpha(1.f),
	_state(State::APEARENCE)
{
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
	_t += SPEED * dt;
	if (_t > 2 * math::PI) {
		_t = 0.f;
	}
	_scale = 1.f + DELTA_SCALE * sinf(_t);
	_alpha = math::clamp(0.f, 1.f, _alpha + _multiplier * dt);
}

void TextAnimated::setState(TextAnimated::State newState) {
	_state = newState;
	if (_state == State::DISSAPEARENCE) {
		_multiplier = -1.f;
	}
	else if (_state == State::APEARENCE) {
		_multiplier = 1.f;
		_t = 0.f;
	}
}