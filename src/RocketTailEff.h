#pragma once

class RocketTailEff
{
private:	
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	float _x, _y;
public:
	RocketTailEff();
	typedef boost::shared_ptr<RocketTailEff> HardPtr;
	void draw();
	void update(float dt);
	void reset();
};