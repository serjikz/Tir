#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
	: _x(0),
	_speed(0),
	_angle(0),
	_t(0)	
{
	_tank= Core::resourceManager.Get<Render::Texture>("Tank");
};

void Tank::update(float dt) {
	_speed *= FRICTION_FORCE;
	_scaleY = 1.f + 0.01f * _speed * sinf(dt);	
	int pos =  _x + (int) _speed;
	_x = math::clamp(0, Render::device.Width() - _tank->getBitmapRect().Width(), pos);
	_angle *= FRICTION_FORCE;
	_t = dt;
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
	//_dt *= -1;
	//_angle = -10;
	//_t = 0;
	_angle = math::clamp(-15.f, 0.f, _angle - 0.5f *_t);
	//_speed = -MOVE_DX;	
	_speed = math::clamp(-MOVE_DX + 0.f, 0.f, _speed - MOVE_DX * _t);
}

void Tank::moveRight() {
	//_dt *= -1;
	_angle = math::clamp(0.f, 15.f, _angle + 0.5f * _t);
	//_t = 0;
	//_speed = MOVE_DX;
	_speed = math::clamp(0.f, MOVE_DX + 0.f, _speed + MOVE_DX * _t);
}
