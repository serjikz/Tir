#include "stdafx.h"
#include "ArrowHintPanel.h"

ArrowHintPanel::ArrowHintPanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_isMirrored(false),
	_alpha(0.5f), 
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
		_alpha = math::clamp(0.f, MAX_ALPHA, _alpha + _direction * dt);
		if (_state == State::DISSAPEARENCE) {
			if (_isMirrored) {
				_dx = math::clamp(-MAX_DX, 0.f, _dx - DISSAPEARENCE_SPEED * dt);
			}
			else {
				_dx = math::clamp(0.f, MAX_DX, _dx + DISSAPEARENCE_SPEED * dt);
			}
		}
		else {
			_dx = 1.f + DELTA_POS * sinf(_t);
			if (_isMirrored) {
				_dx *= -1;
			}
		}
		_t += _speed * dt;
		if (_t > 2 * math::PI) {
			_t = 0.f;
		}
		if (_alpha < EPS) {
			_state = State::HIDEN;
		}
	}
}

void ArrowHintPanel::setState(InterfaceState newState) {
	if (newState == InterfaceState::PLAY) {
		Panel::setState(State::DISSAPEARENCE);

	} else if (newState == InterfaceState::TAP_TO_PLAY) {
		Panel::setState(State::APEARENCE);
		_t = 0.f;
	}
}
