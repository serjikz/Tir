#pragma once
#include "Missile.h"
#include "Enemy.h"

class Cannon
{
private:	
	const float EPS = 0.001f;
	Render::Texture* _tex;
	short int _x, _y;
	short int _dx, _dy;
	float _angle;
	float _scaleY;
	float _t;
	float MIN_ANGLE;
	float MAX_ANGLE;
	float INTERTIA_MOVE;
	float INTERTIA_SPEED;
	float CANNON_X0;
	float CANNON_Y0;
	FPoint _directionVec;
	std::deque<Missile::HardPtr> _missiles;
	short int _missilesAvailable;
	size_t _missilesInitValue;
	FPoint _textureCenter;
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	size_t _missileSpeed;
public:
	Cannon(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cannon> HardPtr;
	void draw();
	void update(float dt, float tankPosx, std::vector<Enemy::HardPtr>& enemies);
	void shot(IPoint atTankPos);
	bool isAllMissilesExploaded();
	void reloadMissiles();
};