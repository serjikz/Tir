#include "stdafx.h"


Dirt::Dirt(rapidxml::xml_node<>* settings)
{
	_y = Xml::GetFloatAttributeOrDef(settings, "dirtY", 0);
	_x1 = Xml::GetFloatAttributeOrDef(settings, "dirtX1", 0);
	_x2 = Xml::GetFloatAttributeOrDef(settings, "dirtX2", 0);
}

void Dirt::draw() {
	_effCont.Draw();
}

void Dirt::update(float dt) {
	_effCont.Update(dt);
}

void Dirt::reset(float speed) {
	_exhaustGasEff = _effCont.AddEffect("Dirt");
	if (speed > 0) {
		_exhaustGasEff->posX = _x1;
	}
	else {
		_exhaustGasEff->posX = _x2;
		_exhaustGasEff->SetScale(-1.f, 1.f);
	}
	_exhaustGasEff->posY = _y;
	_exhaustGasEff->Reset();
}