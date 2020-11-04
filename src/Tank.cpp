#include "stdafx.h"


Tank::Tank(rapidxml::xml_node<>* settings)
	: _x(START_X),
	_speed(0),
	_angle(0)
{	
	rapidxml::xml_node<>* tankSpeed = settings->first_node("TankSpeed");
	MAX_SPEED = Xml::GetFloatAttributeOrDef(tankSpeed, "maxSpeed", 0.f);
	MOVE_DX = Xml::GetFloatAttributeOrDef(tankSpeed, "moveDX", 0.f);
	MAX_ANGLE = Xml::GetFloatAttributeOrDef(tankSpeed, "maxAngle", 0.f);
	ANGLE_COEF = Xml::GetFloatAttributeOrDef(tankSpeed, "angleCoef", 0.f);
	FRICTION_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "frictionForce", 0.f);
	GRAVITY_FORCE = Xml::GetFloatAttributeOrDef(tankSpeed, "gravityForce", 0.f);
	_tex = Core::resourceManager.Get<Render::Texture>("Tank");
	rapidxml::xml_node<>* wheels = settings->first_node("Wheels");
	rapidxml::xml_node<>* wheel = wheels->first_node("Wheel");
	while (wheel) {
		_wheels.push_back(Wheel::HardPtr(new Wheel(wheel)));
		wheel = wheel->next_sibling();
	}
	rapidxml::xml_node<>* cannon = settings->first_node("Cannon");
	rapidxml::xml_node<>* guiSettings = settings->first_node("GUI");
	_cannon = Cannon::HardPtr(new Cannon(cannon));
	_exhaustGasEff = _effCont.AddEffect("ExhaustGas");
	_exhaustGasEff->posY = Xml::GetFloatAttributeOrDef(settings, "exhaustGasPosY", 0);
	_exhaustGasEff->posX = Xml::GetFloatAttributeOrDef(settings, "exhaustGasPosX", 0);
	_dirtEff = Dirt::HardPrt(new Dirt(settings));
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
};

void Tank::update(float dt, std::vector<Enemy::HardPtr>& enemies) {
	_x = math::clamp(0.f, (float)Render::device.Width() - _tex->getBitmapRect().Width(), _x + _speed * dt);
	_angle *= GRAVITY_FORCE;
	_speed *= FRICTION_FORCE;
	if (fabs(_speed) < 0.1f) {
		_speed = 0.f;
	}
	for (int i = 0; i < (int)_wheels.size(); i++) {
		_wheels[i]->update(-_speed * dt);
	}
	_cannon->update(dt, _x + _tex->getBitmapRect().Width() / 2.f, enemies);
	_effCont.Update(dt);
	_dirtEff->update(dt);
}

void Tank::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x + _textureCenter.x, _textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	//Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_cannon->draw();
	_tex->Draw();	
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
	_cannon->shot(IPoint(_x + _textureCenter.x, _textureCenter.y));
}

bool Tank::isAllRocketsExploaded() {
	return _cannon->isAllRocketsExploaded();
}

void Tank::reloadRockets() {
	_cannon->reloadRockets();
}

void Tank::setMissileSpeed(int speed) {
	_cannon->setMissileSpeed(speed);
}