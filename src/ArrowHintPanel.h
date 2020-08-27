#pragma once
#include "Panel.h"

class ArrowHintPanel : public Panel
{
private:
	const float DELTA_POS = 4.f;
	bool _isMirrored;
	float _alpha;
	float _dx;
public:
	ArrowHintPanel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<ArrowHintPanel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(Panel::State newState);
};