#pragma once

class MissileExplodeEff
{
private:	
	const std::string ENEMY_EXPL_EFF = "EnemyExploded";
	const std::string MISSILE_EXPL_EFF = "MissileExploded";
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
public:
	MissileExplodeEff();
	typedef boost::shared_ptr<MissileExplodeEff> HardPtr;
	void draw();
	void update(float dt);
	void reset(int x, int y);
	bool isFinished();
};