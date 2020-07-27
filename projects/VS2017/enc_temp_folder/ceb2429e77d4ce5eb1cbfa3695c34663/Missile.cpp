#include "stdafx.h"
#include "Missile.h"

Missile::Missile(float x0, float y0)
	: _x(0),
	_y(0),
	_scale(1.f),
	_speed(1.f)
{
	//std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	//_cloud = Core::resourceManager.Get<Render::Texture>(textureID);
	
}

void Missile::draw() {

}

void Missile::update(float dt) {
	
}