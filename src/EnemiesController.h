#pragma once
#include "Enemy.h"


class EnemiesController
{
	const std::string ENEMY_EXPL_EFF = "EnemyExploded";
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	std::vector <Enemy::HardPtr> _enemies;
	size_t _enemiesToHit;
	void explode(const FPoint &pos);
public:
	EnemiesController();
	typedef boost::shared_ptr<EnemiesController> HardPtr;
	void createNewEnemies();
	void checkEnemiesCollision();
	void checkMissilesHit(std::vector<Missile::HardPtr> missiles);
	void update(float dt);
	void draw();
	size_t getEnemiesToHit();
	const std::vector <Enemy::HardPtr>& getObjects() const;
};
