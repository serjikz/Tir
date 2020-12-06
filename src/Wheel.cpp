#include "stdafx.h"


Wheel::Wheel(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_angle(math::random(0, 360))	
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_wheel = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "dx", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "dy", 0);
	_textureCenter = FPoint(_wheel->getBitmapRect().Width() / 2, _wheel->getBitmapRect().Height() / 2);
}

void Wheel::draw() {
	assert(_wheel);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_wheel->Draw();
	Render::device.PopMatrix();
}

void Wheel::update(float dt) {
	_angle += dt;
	if (_angle > 360) {
		_angle = _angle - 360;
	}
}