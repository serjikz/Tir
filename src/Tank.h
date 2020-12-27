#pragma once
#include "Wheel.h"
#include "Cannon.h"
#include "Dirt.h"
#include "Enemy.h"

// Танк

class Tank
{
private:	
	const int START_X = 440;
	float MAX_SPEED;
	float MOVE_DX;
	float MAX_ANGLE;
	float FRICTION_FORCE;
	float GRAVITY_FORCE;
	float ANGLE_COEF;	
	float _x;
	float _speed;
	float _scaleY;
	float _angle;
	FPoint _textureCenter;
	EffectsContainer _effCont;
	ParticleEffectPtr _exhaustGasEff;
	Render::Texture* _tex;
	std::vector<Wheel::HardPtr> _wheels;	
	Cannon::HardPtr _cannon;
	Dirt::HardPrt _dirtEff;
	enum class State {
		NORMAL,
		MISSILES_OVER,
		NEED_RELOAD
	} _state;
public:
	Tank();
	typedef boost::shared_ptr<Tank> HardPtr;
	void draw();
	void update(float dt);
	void moveLeft();
	void moveRight();
	void shot();
	bool isAllMissilesExploaded();
	void reloadMissiles();
	std::vector<Missile::HardPtr> getMissiles();
};

