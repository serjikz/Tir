#pragma once

class Tank
{
private:	
	const float MAX_SPEED = 35;
	const short int MOVE_DX = 5;
	const float FRICTION_FORCE = 0.96f;
	Render::Texture* _tank;
	short int _x;
	float _speed;
	float _scaleY;
	float _angle;
	float _t;
public:
	Tank();
	typedef boost::shared_ptr<Tank> HardPrt;
	void draw();
	void update(float dt);
	void moveLeft();
	void moveRight();
};

