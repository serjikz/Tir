#include "stdafx.h"
#include "Cloud.h"

Cloud::Cloud(rapidxml::xml_node<>* settings)
	: _x(0),
	_y(0),
	_scale(1.f),
	_speed(1.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_cloud = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "dx", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "dy", 0);
	ALPHA = Xml::GetFloatAttributeOrDef(settings, "alpha", 0.5f);
	MIN_SCALE = Xml::GetFloatAttributeOrDef(settings, "minScale", 1.f);
	MAX_SCALE = Xml::GetFloatAttributeOrDef(settings, "maxScale", 1.f);
	MIN_SPEED = Xml::GetFloatAttributeOrDef(settings, "minSpeed", 1.f);
	MAX_SPEED = Xml::GetFloatAttributeOrDef(settings, "maxSpeed", 1.f);
	MIN_Y = Xml::GetFloatAttributeOrDef(settings, "minY", 300);
	MAX_Y = Xml::GetFloatAttributeOrDef(settings, "maxY", 500);
}

void Cloud::draw() {
	assert(_cloud);
	FPoint textureCenter = FPoint(_cloud->getBitmapRect().Width() / 2.f, _cloud->getBitmapRect().Height() / 2.f);
	Render::BeginAlphaMul(ALPHA);
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixScale(_scale);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_cloud->Draw();
	Render::device.PopMatrix();
	Render::EndAlphaMul();
}

void Cloud::update(float dt) {
	_x -= _speed * dt;
	float leftBottomX = _x + _cloud->getBitmapRect().Width();
	if (leftBottomX < 0) {
		_scale = math::random(MIN_SCALE, MAX_SCALE);
		_speed = math::random(MIN_SPEED, MAX_SPEED);
		_y = math::random(MIN_Y, MAX_Y);
		_x = Render::device.Width() + _scale * _cloud->getBitmapRect().Width();
	}
}