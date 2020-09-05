#pragma once
#include "Enemy.h"
#include "MissileTailEff.h"
#include "MissileExplodeEff.h"

class Missile
{
private:	
	const float SPEED = 500;
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
	bool _exploded;
	MissileTailEff::HardPtr _missileTailEff;
	MissileExplodeEff::HardPtr _missileExplEff;
	void explode();
public:
	Missile(FPoint directionVec, float angle, float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
	bool isNotVisible();
	void tryHit(std::vector<Enemy::HardPtr> &enemies);
	FPoint getCenterPos() const;
	FPoint getMoveVec() const;
	float getMass() const;	
	void bounceWith(Enemy::HardPtr enemy);
};