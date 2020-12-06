#include "stdafx.h"


MissileExplodeEff::MissileExplodeEff()
{
}

void MissileExplodeEff::draw() {
	Render::device.PushMatrix();
	Render::device.ResetMatrix();
	_effCont.Draw();
	Render::device.PopMatrix();
}

void MissileExplodeEff::update(float dt) {
	_effCont.Update(dt);
}

void MissileExplodeEff::reset(int x, int y, bool enemyDestroyed) {
	if (enemyDestroyed) {
		_eff = _effCont.AddEffect(ENEMY_EXPL_EFF);
	}
	else {
		_eff = _effCont.AddEffect(MISSILE_EXPL_EFF);
	}
	_eff->posX = x;
	_eff->posY = y;
	_eff->Reset();
}

bool MissileExplodeEff::isFinished() {
	return _effCont.IsFinished();
}