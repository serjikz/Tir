#pragma once

class Missile
{
private:	
	Render::Texture* _cloud;
	short int _x, _y;
	float _scale;
	float _speed;
	float ALPHA;
	float MIN_SCALE;
	float MAX_SCALE;
	float MIN_SPEED;
	float MAX_SPEED;
	float MIN_Y;
	float MAX_Y;
public:
	Missile(float x0, float y0);
	typedef boost::shared_ptr<Missile> HardPtr;
	void draw();
	void update(float dt);
};