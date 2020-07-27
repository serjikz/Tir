#include "stdafx.h"
#include "Tank.h"

Tank::Tank() //singleton?
	: _x(0),
	_speed(0),
	_angle(0)
{	
	Xml::RapidXmlDocument tankSettingsXml("Settings.xml");
	rapidxml::xml_node<>* root = tankSettingsXml.first_node();
	rapidxml::xml_node<>* tankSpeed = root->first_node("TankSpeed");
	MAX_SPEED = Xml::GetFloatAttributeOrDef(tankSpeed, "maxSpeed", 0.f);
	MOVE_DX = Xml::GetFloatAttributeOrDef(tankSpeed, "moveDX", 0.f);
	MAX_ANGLE = Xml::GetFloatAttributeOrDef(tankSpeed, "maxAngle", 0.f);
	ANGLE_COEF = Xml::GetFloatAttributeOrDef(tankSpeed, "angleCoef", 0.f);
	FRICTION_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "frictionForce", 0.f);
	GRAVITY_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "gravityForce", 0.f);
	SWING_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "swingForce", 0.f);
	_tex = Core::resourceManager.Get<Render::Texture>("Tank");
	rapidxml::xml_node<>* wheels = root->first_node("Wheels");
	rapidxml::xml_node<>* wheel = wheels->first_node("Wheel");
	while (wheel) {
		_wheels.push_back(Wheel::HardPtr(new Wheel(wheel)));
		wheel = wheel->next_sibling();
	}
	rapidxml::xml_node<>* cannon = root->first_node("Cannon");
	_cannon = Cannon::HardPtr(new Cannon(cannon));
	_exhaustGasEff = _effCont.AddEffect("ExhaustGas");
	_exhaustGasEff->posY = Xml::GetFloatAttributeOrDef(root, "exhaustGasPosY", 0);
	_exhaustGasEff->posX = Xml::GetFloatAttributeOrDef(root, "exhaustGasPosX", 0);
	_dirtEff = Dirt::HardPrt(new Dirt(root));
};

void Tank::update(float dt) {
	_x = math::clamp(0.f, (float)Render::device.Width() - _tex->getBitmapRect().Width(), _x + _speed * dt);
	_angle *= GRAVITY_FORCE;
	_speed *= FRICTION_FORCE;
	if (fabs(_speed) < 0.1f) {
		_speed = 0.f;
	}
	for (int i = 0; i < (int)_wheels.size(); i++) {
		_wheels[i]->update(-_speed * dt);
	}
	_cannon->update(dt, _x + _tex->getBitmapRect().Width() / 2.f);
	_effCont.Update(dt);
	_dirtEff->update(dt);
}

void Tank::draw() {
	FPoint textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x + textureCenter.x, textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	//Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_tex->Draw();
	_cannon->draw();
	
	for (int i = 0; i < (int)_wheels.size(); i++) {
		_wheels[i]->draw();
	}
	_effCont.Draw();
	_dirtEff->draw();
	Render::device.PopMatrix();	
}

void Tank::moveLeft() {
	_speed = math::clamp(-MAX_SPEED, 0.f, _speed - MOVE_DX);
	_angle = math::clamp(-MAX_ANGLE, 0.f, _angle - ANGLE_COEF);
	_dirtEff->reset(_speed);
}

void Tank::moveRight() {
	_speed = math::clamp(0.f, MAX_SPEED, _speed + MOVE_DX);
	_angle = math::clamp(0.f, MAX_ANGLE, _angle + ANGLE_COEF);
	_dirtEff->reset(_speed);
}

void Tank::shot() {
	FPoint textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	_cannon->shot(IPoint(_x + textureCenter.x, textureCenter.y));
}