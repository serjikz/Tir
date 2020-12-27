#pragma once
#include "Enemy.h"

/*
 * Данный класс управляет целями на экране
*/

class EnemiesController
{
	const std::string ENEMY_EXPL_EFF = "EnemyExploded";
	const std::string MISSILE_EXPL_EFF = "MissileExploded";
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	std::vector <Enemy::HardPtr> _enemies;
	size_t _enemiesToHit;
	void explodeEnemy(const FPoint &pos);
	void explodeMissile(const FPoint& pos);
	void tryHitSomeEnemy(Missile::HardPtr& missile);
public:
	EnemiesController();
	typedef boost::shared_ptr<EnemiesController> HardPtr;
	void createNewEnemies();
	void checkEnemiesCollision();
	void checkMissilesHit(std::vector<Missile::HardPtr>& missiles);
	void update(float dt);
	void draw();
	size_t getEnemiesToHit();
	const std::vector <Enemy::HardPtr>& getObjects() const;
};
