#include "stdafx.h"


MissileTailEff::MissileTailEff()
{
	_x = TAIL_X;
	_y = 0;
}

void MissileTailEff::draw() {
	_effCont.Draw();
}

void MissileTailEff::update(float dt) {
	_effCont.Update(dt);
}

void MissileTailEff::reset() {
	_eff = _effCont.AddEffect(ROCKET_TAIL_EFF);
	_eff->posX = _x;
	_eff->posY = _y;
	_eff->Reset();
}