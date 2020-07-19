#pragma once

class Wheel
{
private:	
	Render::Texture* _wheel;
	short int _x, _y;
	/*float _speed;
	float _scale;
	float _angle;
	float _t;*/
public:
	Wheel();
	typedef boost::shared_ptr<Wheel> HardPrt;
	void draw();
	void init();
	void update(float dt);
};