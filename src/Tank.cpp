#include "stdafx.h"
#include "Tank.h"

Tank::Tank()
	: _x(0),
      _y(0)
{
	_tank= Core::resourceManager.Get<Render::Texture>("Tank");
};

void Tank::draw() {
	assert(_tank);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	_tank->Draw();
	Render::device.PopMatrix();	
}


