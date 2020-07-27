#pragma once

class Missile
{
private:	
	Render::Texture* _tex;
	float _x0, _y0;
	float _t;
	FPoint _directionVec;
	float _dx, _dy;
	float _angle;
	

public:
	Missile(FPoint directionVec, float angle, float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
};