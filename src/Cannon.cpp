#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(rapidxml::xml_node<>* settings)
	: _x(0),
	_y(0),
	_dx(0),
	_dy(0),
	_angle(0),
	_scaleY(1.f),
	_t(1.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	MIN_ANGLE = Xml::GetFloatAttributeOrDef(settings, "minAngle", -90);
	MAX_ANGLE = Xml::GetFloatAttributeOrDef(settings, "maxAngle", 90);
	INTERTIA_MOVE = Xml::GetFloatAttributeOrDef(settings, "inertiaMove", 0);
	INTERTIA_SPEED = Xml::GetFloatAttributeOrDef(settings, "inertiaSpeed", 0);
}

void Cannon::draw() {
	assert(_tex);
	FPoint textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x - _dx, _y - _dy, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-textureCenter.x, 0, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Cannon::update(float dt, float tankPosx) {
	IPoint mousePos = Core::mainInput.GetMousePos();
	IPoint v1 = IPoint(mousePos.x - tankPosx, mousePos.y - _tex->getBitmapRect().Height());
	IPoint v2 = IPoint(0, 1);
	float len = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
	FPoint v3 = FPoint(v1.x / len, v1.y / len);
	_angle = math::clamp(MIN_ANGLE, MAX_ANGLE, 180.f / math::PI * (float) acos(v3.y));
	if (v1.x > 0) {
		_angle *= -1;
	}
	_t = math::clamp(0.f, 1.f, _t + INTERTIA_SPEED * dt);
	_dx = math::lerp(int(INTERTIA_MOVE * v3.x), 0, _t);
	_dy = math::lerp(int(INTERTIA_MOVE * v3.y ), 0, _t);
}

void Cannon::shot() {
	_t = 0;
	_missiles.push_back(Missile::HardPtr(new Missile(_x, _y)));
}