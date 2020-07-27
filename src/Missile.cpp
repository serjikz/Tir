#include "stdafx.h"
#include "Missile.h"

Missile::Missile(FPoint directionVec, float angle, float x0, float y0)
	: _directionVec(directionVec),
	_angle(angle)
	, _t(0.f),
	_dx(0.f),
	_dy(0.f),
	_x0(x0),
	_y0(y0)
{
	_tex = Core::resourceManager.Get<Render::Texture>("Missile");
	_t = 0.f;
}

void Missile::draw() {
	FPoint textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	Render::device.PushMatrix();
	Render::device.ResetMatrix();
	Render::device.MatrixTranslate(_x0 + _dx, _y0 + _dy, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-textureCenter.x, 0, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Missile::update(float dt) {
	_t = math::clamp(0.f, 5.f, _t + 10 * dt);
	_dx += 100.f * _directionVec.x * dt;
	_dy += 100.f * _directionVec.y * dt;
}