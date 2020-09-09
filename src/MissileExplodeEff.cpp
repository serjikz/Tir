#include "stdafx.h"
#include "MissileExplodeEff.h"

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
		_eff = _effCont.AddEffect("EnemyExploded");
	}
	else {
		_eff = _effCont.AddEffect("MissileExploded");
	}
	_eff->posX = x;
	_eff->posY = y;
	_eff->Reset();
}

bool MissileExplodeEff::isFinished() {
	return _effCont.IsFinished();
}