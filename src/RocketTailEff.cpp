#include "stdafx.h"
#include "RocketTailEff.h"

RocketTailEff::RocketTailEff()
{
	_x = 12;
	_y = 0;
}

void RocketTailEff::draw() {
	_effCont.Draw();
}

void RocketTailEff::update(float dt) {
	_effCont.Update(dt);
}

void RocketTailEff::reset() {
	_eff = _effCont.AddEffect("RocketTail");
	_eff->posX = _x;
	_eff->posY = _y;
	_eff->Reset();
}