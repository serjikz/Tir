#pragma once

class MissileExplodeEff
{
private:	
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
public:
	MissileExplodeEff();
	typedef boost::shared_ptr<MissileExplodeEff> HardPtr;
	void draw();
	void update(float dt);
	void reset(int x, int y, bool enemyDestroyed = false);
	bool isFinished();
};