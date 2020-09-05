#include "stdafx.h"
#include "Missile.h"

Missile::Missile(FPoint directionVec, float angle, float x0, float y0)
	:_angle(angle)
	, _t(0.f),
	_dx(0.f),
	_dy(0.f),
	_x0(x0),
	_y0(y0),
	_exploded(false)
{
	float alpha = atan2(directionVec.y, directionVec.x);
	_moveVec = FPoint(SPEED * cos(alpha), SPEED * sin(alpha));
	_tex = Core::resourceManager.Get<Render::Texture>("Missile");
	_t = 0.f;
	_missileTailEff = MissileTailEff::HardPtr(new MissileTailEff());
	_missileTailEff->reset();
	_missileExplEff = MissileExplodeEff::HardPtr(new MissileExplodeEff());
}

void Missile::draw() {
	if (!_exploded) {
		FPoint textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
		Render::device.PushMatrix();
		Render::device.ResetMatrix();
		Render::device.MatrixTranslate(_x0 + _dx, _y0 + _dy, 0);
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
		Render::device.MatrixTranslate(-textureCenter.x, 0, 0);
		_tex->Draw();
		_missileTailEff->draw();
		Render::device.PopMatrix();
	}
	else {
		_missileExplEff->draw();
	}
}

void Missile::update(float dt) {
	if (_exploded) {
		_missileExplEff->update(dt);
	}
	else {
		_missileTailEff->update(dt);
		_t = math::clamp(0.f, LIFE_TIME, _t + dt);
		_dx += _moveVec.x * dt;
		_moveVec.y -= G * _t * _t / 2.f;
		_dy += _moveVec.y * dt;
		_angle = -90.f + 180.f / math::PI * atan2(_moveVec.y, _moveVec.x);
	}
	if (!_exploded && (_y0 + _dy < MIN_Y)) {
		explode();
		_missileExplEff->reset(_x0 + _dx, MIN_Y);
	}
}

bool Missile::isNotVisible() {
	IRect screen = IRect(0, 0, Render::device.Width(), 2 * Render::device.Height());
	IRect textureRect = IRect(_x0 + _dx, _y0 + _dy, _tex->getBitmapRect().Width(), _tex->getBitmapRect().Height());
	return (_exploded && _missileExplEff->isFinished()) || !textureRect.Intersects(screen);
}

void Missile::tryHit(std::vector<Enemy::HardPtr> &enemies) {
	if (_exploded) {
		return;
	}
	for (auto it = enemies.begin(); it != enemies.end();) {
		FPoint interactionVec = (*it)->getCenterPos() - this->getCenterPos();
		float sqrLen = pow(interactionVec.x, 2) + pow(interactionVec.y, 2);
		float r = _tex->getBitmapRect().Height() / 2.f + (*it)->getTextureRect().Width() / 2.f;
		if (sqrLen < r * r) {
			bounceWith(*it);
			(*it)->reduceHealth();
			if ((*it)->getHealth() <= 0) {
				it = enemies.erase(it);
				return;
			}
			else {
				_missileExplEff->reset(this->getCenterPos().x, this->getCenterPos().y);
			}
		}
		it++;
	}
}

FPoint Missile::getCenterPos() const{
	return FPoint(_x0 + _dx, _y0 + _dy);
}

FPoint Missile::getMoveVec() const {
	return _moveVec;
}

float Missile::getMass() const {
	return M;
}

void Missile::bounceWith(Enemy::HardPtr enemy) {
	FPoint interactionVec = enemy->getCenterPos() - getCenterPos();
	float alpha = math::atan(interactionVec.y, interactionVec.x);
	float cosA = cos(alpha);
	float sinA = sin(alpha);
	FPoint enemyV = enemy->getMoveVec();
	// проекция скорости на вектор взаимодействия
	float p1X = _moveVec.x * cosA + _moveVec.y * sinA;
	float p2X = enemyV.x * cosA + enemyV.y * sinA;
	// проекция на линию перпендикулярную вектору взамиодействия
	float p1Y = _moveVec.y * cosA - _moveVec.x * sinA;
	float p2Y = enemyV.y * cosA - enemyV.x * sinA;
	// новые скорости тел
	float m1 = M;
	float m2 = enemy->getMass();
	float p = m1 * p1X + m2 * p2X;
	float v = p1X - p2X;
	float v2f = (p + v * m1) / (m1 + m2);
	p2X = v2f;
	// обратное проецирование
	enemy->setMoveVec(p2X * cosA - p2Y * sinA, p2Y * cosA + p2X * sinA);
	explode();
}

void Missile::explode() {
	_moveVec.x = 0.f;
	_moveVec.y = 0.f;
	_exploded = true;
}
