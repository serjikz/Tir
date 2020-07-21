#pragma once
#include "Wheel.h"
#include "Cannon.h"
#include "Dirt.h"

class Tank
{
private:	
	float MAX_SPEED;
	float MOVE_DX;
	float MAX_ANGLE;
	float FRICTION_FORCE;
	float GRAVITY_FORCE;
	float ANGLE_COEF;	
	short int _x;
	float _speed;
	float _scaleY;
	float _angle;
	EffectsContainer _effCont;
	ParticleEffectPtr _exhaustGasEff;
	Render::Texture* _tank;
	std::vector<Wheel::HardPrt> _wheels;
	Cannon::HardPtr _cannon;
	Dirt::HardPrt _dirtEff;
public:
	Tank();
	typedef boost::shared_ptr<Tank> HardPrt;
	void draw();
	void update(float dt);
	void moveLeft();
	void moveRight();
	void shot();
};

