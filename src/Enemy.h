#pragma once

class Enemy
{
private:	
	float MAX_SPEED;
	float MOVE_DX;
	float MAX_ANGLE;
	float FRICTION_FORCE;
	float GRAVITY_FORCE;
	float SWING_FORCE;
	float ANGLE_COEF;	
	float _x;
	float _speed;
	float _scaleY;
	float _angle;
	EffectsContainer _effCont;
	Render::Texture* _texture;
public:
	Enemy(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Enemy> HardPtr;
	void draw();
	void update(float dt);
};

