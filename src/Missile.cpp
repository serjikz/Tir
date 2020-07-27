#include "stdafx.h"
#include "Missile.h"

Missile::Missile(float x0, float y0)
	: _x(x0),
	_y(y0)
{
	_tex = Core::resourceManager.Get<Render::Texture>("Missile");
	_t = 0.f;

	
}

void Missile::draw() {

}

void Missile::update(float dt) {
	
}