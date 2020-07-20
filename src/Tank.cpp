#include "stdafx.h"
#include "Tank.h"

Tank::Tank() //singleton?
	: _x(0),
	_speed(0),
	_angle(0),
	_t(0)	
{	
	Xml::RapidXmlDocument tankSettingsXml("Settings.xml");
	rapidxml::xml_node<>* root = tankSettingsXml.first_node();
	rapidxml::xml_node<>* tankSpeed = root->first_node("TankSpeed");
	MAX_SPEED = Xml::GetFloatAttributeOrDef(tankSpeed, "maxSpeed", 0.f);
	MOVE_DX = Xml::GetFloatAttributeOrDef(tankSpeed, "moveDX", 0.f);
	MAX_ANGLE = Xml::GetFloatAttributeOrDef(tankSpeed, "maxAngle", 0.f);
	ANGLE_COEF = Xml::GetFloatAttributeOrDef(tankSpeed, "angleCoef", 0.f);
	FRICTION_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "frictionForce", 0.f);
	_tank = Core::resourceManager.Get<Render::Texture>("Tank");
	rapidxml::xml_node<>* wheels = root->first_node("Wheels");
	rapidxml::xml_node<>* wheel = wheels->first_node("Wheel");
	while (wheel) {
		_wheels.push_back(Wheel::HardPrt(new Wheel(wheel)));
		wheel = wheel->next_sibling();
	}
	rapidxml::xml_node<>* cannon = root->first_node("Cannon");
	_cannon = Cannon::HardPtr(new Cannon(cannon));
};

void Tank::update(float dt) {
	_speed *= FRICTION_FORCE;
	_scaleY = 1.f + 0.01f * _speed * sinf(dt);	
	int pos =  _x + (int) _speed;
	_x = math::clamp(0, Render::device.Width() - _tank->getBitmapRect().Width(), pos);
	_angle *= FRICTION_FORCE;
	_t = dt;
	for (int i = 0; i < (int)_wheels.size(); i++) {
		_wheels[i]->update(-_speed);
	}
	_cannon->update(_x + _tank->getBitmapRect().Width() / 2.f);
}

void Tank::draw() {
	assert(_tank);
	FPoint textureCenter = FPoint(_tank->getBitmapRect().Width() / 2.f, _tank->getBitmapRect().Height() / 2.f);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x + textureCenter.x, textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_cannon->draw();
	_tank->Draw();
	for (int i = 0; i < (int)_wheels.size(); i++) {
		_wheels[i]->draw();
	}
	Render::device.PopMatrix();	

	
	
}

void Tank::moveLeft() {
	_angle = math::clamp(-MAX_ANGLE, 0.f, _angle - ANGLE_COEF *_t);
	_speed = math::clamp(-MOVE_DX + 0.f, 0.f, _speed - MOVE_DX * _t);
}

void Tank::moveRight() {
	_angle = math::clamp(0.f, MAX_ANGLE, _angle + ANGLE_COEF * _t);
	_speed = math::clamp(0.f, MOVE_DX + 0.f, _speed + MOVE_DX * _t);
}
