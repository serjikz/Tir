#include "stdafx.h"
#include "Panel.h"

Panel::Panel(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_angle(0)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "dx", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "dy", 0);
}

void Panel::draw() {
	/*assert(_wheel);
	FPoint textureCenter = FPoint(_wheel->getBitmapRect().Width() / 2, _wheel->getBitmapRect().Height() / 2 );
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_wheel->Draw();
	Render::device.PopMatrix();*/
}

void Panel::update(float dt) {
	
}