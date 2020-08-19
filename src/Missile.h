#pragma once
#include "Enemy.h"

class Missile
{
private:	
	const float SPEED = 900.f;
	const float G = 9.8;
	const float LIFE_TIME = 150.f;
	const float M = 5.f;
	Render::Texture* _tex;
	FPoint _moveVec;
	float _x0, _y0;
	float _t;	
	float _dx, _dy;
	float _angle;
	bool _exploaded;
	void explode();
public:
	Missile(FPoint directionVec, float angle, float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
	bool isNotVisible();
	void tryHit(const std::vector<Enemy::HardPtr> &enemies);
	FPoint getCenterPos() const;
	FPoint getMoveVec() const;
	float getMass() const;	
	void bounceWith(Enemy::HardPtr enemy);
};