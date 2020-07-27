#pragma once

class Missile
{
private:	
	Render::Texture* _tex;
	float _x, _y;
	float _t;

public:
	Missile(float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
};