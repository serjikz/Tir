#include "stdafx.h"


Tank::Tank()
	: _x(START_X),
	_speed(0),
	_angle(0),
	_state(State::NORMAL)
{	
	// Инициализируем из файла
	rapidxml::xml_node<>* settings = XmlSettings::getInstance()->getTankNode();
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
	rapidxml::xml_node<>* cannonSettings = settings->first_node("Cannon");
	rapidxml::xml_node<>* guiSettings = settings->first_node("GUI");
	_cannon = Cannon::HardPtr(new Cannon(cannonSettings));
	_exhaustGasEff = _effCont.AddEffect("ExhaustGas");
	_exhaustGasEff->posY = Xml::GetFloatAttributeOrDef(settings, "exhaustGasPosY", 0);
	_exhaustGasEff->posX = Xml::GetFloatAttributeOrDef(settings, "exhaustGasPosX", 0);
	_dirtEff = Dirt::HardPrt(new Dirt(settings));
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
};

void Tank::update(float dt) {
	// При обновлении учитываем положение относительно границ экрана
	_x = math::clamp(0.f, (float)Render::device.Width() - _tex->getBitmapRect().Width(), _x + _speed * dt);
	// Опускаем корму танка силой тяжести
	_angle *= GRAVITY_FORCE;
	// Тормозим танк силой трения
	_speed *= FRICTION_FORCE;
	if (fabs(_speed) < 0.1f) {
		_speed = 0.f;
	}
	// Вращаем колеса
	for (const auto& wheel : _wheels) {
		wheel->update(-_speed * dt);
	}
	// Обновляем пушку и эффекты
	_cannon->update(dt, _x + _tex->getBitmapRect().Width() / 2.f);
	_effCont.Update(dt);
	_dirtEff->update(dt);
	// Изменяем состояние танка
	switch (_state) {
	case State::NORMAL:
		if (isAllMissilesExploaded()) {
			_state = State::MISSILES_OVER;
		}
		break;
	case State::MISSILES_OVER:
		Message msg = Message(Message("ShowStats", "MissilesAreOver"));
		Core::guiManager.getLayer("TestLayer")->getWidget("GameFieldWidget")->AcceptMessage(msg);
		_state = State::NEED_RELOAD;
		break;
	}
}

void Tank::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x + _textureCenter.x, _textureCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	//Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_cannon->draw();
	_tex->Draw();	
	for (const auto& wheel: _wheels) {
		wheel->draw();
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

bool Tank::isAllMissilesExploaded() {
	return _cannon->isAllMissilesExploaded();
}

void Tank::reloadMissiles() {
	_cannon->reloadMissiles();
	_state = State::NORMAL;
}

std::vector<Missile::HardPtr> Tank::getMissiles() {
	return _cannon->getMissiles();
}
