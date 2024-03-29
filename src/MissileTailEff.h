#pragma once

class MissileTailEff
{
private:	
	const int TAIL_X = 12;
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	float _x, _y;
public:
	MissileTailEff();
	typedef boost::shared_ptr<MissileTailEff> HardPtr;
	void draw();
	void update(float dt);
	void reset();
};