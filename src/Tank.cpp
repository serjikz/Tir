#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
	: _x(0),
	_speed(0),
	_angle(0)
	
{
	_tank= Core::resourceManager.Get<Render::Texture>("Tank");
};

void Tank::update() {
	_speed *= FRICTION_FORCE;
	_scaleY = 1.f + 0.04f * sinf(_speed);
	_angle *= FRICTION_FORCE;
	int pos =  _x + (int) _speed;
	_x = math::clamp(0, Render::device.Width() - _tank->getBitmapRect().Width(), pos);
}

void Tank::draw() {
	assert(_tank);
	FPoint textureCenter = FPoint(_tank->getBitmapRect().Width() / 2, _tank->getBitmapRect().Height() / 2);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_tank->Draw();
	Render::device.PopMatrix();	
}

void Tank::moveLeft() {
	_speed = -MOVE_DX;
	if (fabs(_angle) < 1.f) {
		_angle = -7;
	}	
}

void Tank::moveRight() {
	_speed = MOVE_DX;
	if (fabs(_angle) < 1.f) {
		_angle = 7;
	}
}
