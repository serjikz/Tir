#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(rapidxml::xml_node<>* settings)
{	
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_texture = Core::resourceManager.Get<Render::Texture>(textureID);	
	_textureCenter = FPoint(_texture->getBitmapRect().Width() / 2.f, _texture->getBitmapRect().Height() / 2.f);
	_x = Xml::GetFloatAttributeOrDef(settings, "x", 0);
	_y = Xml::GetFloatAttributeOrDef(settings, "y", 0);
	_vecMove.x = Xml::GetFloatAttributeOrDef(settings, "speedX", 0);
	_vecMove.y = Xml::GetFloatAttributeOrDef(settings, "speedY", 0);
	_m = Xml::GetFloatAttributeOrDef(settings, "m", 0);
	_scale = Xml::GetFloatAttributeOrDef(settings, "scale", 1.f);
	_rotationSpeed = Xml::GetFloatAttributeOrDef(settings, "rotationSpeed", 10.f);
	_health = Xml::GetIntAttributeOrDef(settings, "health", 1);
	_speed = _vecMove;
	_t = 0;
	_angle = 0;
	_isBounced = false;
	_enemyLastBounced = 0;
};

void Enemy::update(float dt) {
	_x += _vecMove.x * dt;
	_y += _vecMove.y * dt;
	if (fabs(_vecMove.x) > MAX_SPEED) {
		_vecMove.x *= FRICTION;
	}
	if (fabs(_vecMove.y) > MAX_SPEED) {
		_vecMove.y *= FRICTION;
	}
	if (_t < TIME_TO_BOUNCE * dt) {
		_t += dt; 
	}
	else {
		_isBounced = false;
	}
	checkScreenBounce();
	_angle += _rotationSpeed *dt;
	if (_angle > 360) {
		_angle = _angle - 360;
	}
}

void Enemy::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixScale(_scale, _scale, 1.f);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_texture->Draw();
	Render::device.PopMatrix();	
}

void Enemy::checkScreenBounce() {
	float halfWidth = getTextureRect().Width() / 2.f;
	float halfHeight = getTextureRect().Height() / 2.f;
	if (_x + halfWidth > Render::device.Width()) {
		_vecMove.x *= -1;
		_x = Render::device.Width() - halfWidth;
	}
	else if (_x - halfWidth < 0) {
		_vecMove.x *= -1;
		_x = halfWidth;
	} else if (_y + halfHeight > Render::device.Height()) {
		_y = Render::device.Height() - halfHeight;
		_vecMove.y *= -1;
	} else if (_y - halfHeight < 0) {
		_y = halfHeight;
		_vecMove.y *= -1;
	}
}

IRect Enemy::getTextureRect() const{
	return IRect(_x, _y, _scale * _texture->getBitmapRect().Width(), _scale * _texture->getBitmapRect().Height());
}

FPoint Enemy::getCenterPos() const {
	return FPoint(_x, _y);
}

FPoint Enemy::getMoveVec() const {
	return _vecMove;
}

float Enemy::getMass() {
	return _m;
}

float Enemy::getScale() const {
	return _scale;
}

void Enemy::setMoveVec(float x, float y) {
	_vecMove.x = x;
	_vecMove.y = y;
}

bool Enemy::isIntersect(Enemy::HardPtr anotherEnemy) {
	// расстояние между центрами текстур
	FPoint interactionVec = anotherEnemy->getCenterPos() - this->getCenterPos();
	float sqrLen = pow(interactionVec.x, 2) + pow(interactionVec.y, 2);
	float r = getTextureRect().Width() / 2.f + anotherEnemy->getTextureRect().Width() / 2.f;
	return sqrLen < r * r;
}

void Enemy::bounceWith(Enemy::HardPtr anotherEnemy) {
	// даем время разлететься, чтобы тексутры не "слиплись"
	if (_isBounced && _enemyLastBounced == anotherEnemy) {
		return;
	}
	_t = 0.f;
	_isBounced = true;
	// вектор взаимодействия
	FPoint interactionVec = anotherEnemy->getCenterPos() - this->getCenterPos();
	float alpha = math::atan(interactionVec.y, interactionVec.x);
	float cosA = cos(alpha);
	float sinA = sin(alpha);
	FPoint anotherEnemyV = anotherEnemy->getMoveVec();
	// проекция скорости на вектор взаимодействия
	float p1X = _vecMove.x * cosA + _vecMove.y * sinA;
	float p2X = anotherEnemyV.x * cosA + anotherEnemyV.y * sinA;
	// проекция на линию перпендикулярную вектору взамиодействия
	float p1Y = _vecMove.y * cosA - _vecMove.x * sinA;
	float p2Y = anotherEnemyV.y * cosA - anotherEnemyV.x * sinA;
	// новые скорости тел
	float m1 = _m;
	float m2 = anotherEnemy->getMass();
	float p = m1 * p1X + m2 * p2X;
	float v = p1X - p2X;
	float v2f = (p + v * m1) / (m1 + m2);
	float v1f = v2f - p1X + p2X;
	p1X = v1f;
	p2X = v2f;
	// обратное проецирование
	_vecMove.x = p1X * cosA - p1Y * sinA;
	_vecMove.y = p1Y * cosA + p1X * sinA;
	anotherEnemy->setMoveVec(p2X * cosA - p2Y * sinA, p2Y * cosA + p2X * sinA);
	_enemyLastBounced = anotherEnemy;
}

void Enemy::reduceHealth() {
	_health--;
}

int Enemy::getHealth() {
	return _health;
}