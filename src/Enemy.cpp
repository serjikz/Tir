#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
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
	
};

void Enemy::update(float dt) {
	
}

void Enemy::draw() {
	FPoint textureCenter = FPoint(_texture->getBitmapRect().Width() / 2.f, _texture->getBitmapRect().Height() / 2.f);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x + textureCenter.x, textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	//Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	
	
	Render::device.PopMatrix();	
}
