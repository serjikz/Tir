#pragma once
#include "Enemy.h"
#include "MissileTailEff.h"

// Класс снаряда

class Missile
{
private:	
	const float G = 9.8;
	const float LIFE_TIME = 150.f;
	const float M = 0.15f;
	const int MIN_Y = 10;
	Render::Texture* _tex;
	FPoint _moveVec;
	float _x0, _y0;
	float _t;	
	float _dx, _dy;
	float _angle;
	float _speed;
	bool _exploded;
	MissileTailEff::HardPtr _missileTailEff;
	void explode();
public:
	Missile(FPoint directionVec, float speed, float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
	bool isNotVisible();
	FPoint getCenterPos() const;
	FPoint getMoveVec() const;
	void bounceWith(Enemy::HardPtr enemy);
	float getTextureHeight() const;
};