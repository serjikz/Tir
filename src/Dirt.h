#pragma once

class Dirt
{
private:	
	EffectsContainer _effCont;
	ParticleEffectPtr _exhaustGasEff;
	float _x1, _x2, _y;
public:
	Dirt(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Dirt> HardPrt;
	void draw();
	void update(float dt);
	void reset(float speed);
};