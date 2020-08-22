#include "stdafx.h"
#include "Interface.h"

Interface::Interface(rapidxml::xml_node<>* settings)
{
	rapidxml::xml_node<>* panel = settings->first_node("Panel");
	_rockets = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_time = Panel::HardPtr(new Panel(panel));
	panel = panel->next_sibling();
	_score = Panel::HardPtr(new Panel(panel));
	_tapToPlayText = TextAnimated::HardPtr(new TextAnimated("TAP TO PLAY", Render::device.Width() / 2, Render::device.Height() / 2));
}

void Interface::draw() {
	/*assert(_wheel);
	FPoint textureCenter = FPoint(_wheel->getBitmapRect().Width() / 2, _wheel->getBitmapRect().Height() / 2 );
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_wheel->Draw();
	Render::device.PopMatrix();*/
}

void Interface::update(float dt) {
	
}