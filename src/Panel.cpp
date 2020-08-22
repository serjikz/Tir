#include "stdafx.h"
#include "Panel.h"

Panel::Panel(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_angle(0)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
}

void Panel::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Panel::update(float dt) {
	
}