#pragma once
#include "Enemy.h"

class Missile
{
private:	
	const float SPEED = 400.f;
	Render::Texture* _tex;
	FPoint _moveVec;
	float _x0, _y0;
	float _t;	
	float _dx, _dy;
	float _angle;
	float _m;
	bool _exploaded;
	void explode();
public:
	Missile(FPoint directionVec, float angle, float x0, float y0);
	~Missile();
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