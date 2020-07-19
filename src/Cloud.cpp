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
}

void Cloud::draw() {
	assert(_cloud);
	FPoint textureCenter = FPoint(_cloud->getBitmapRect().Width() / 2, _cloud->getBitmapRect().Height() / 2 );
	Render::BeginAlphaMul(0.3f);
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
		_scale = math::random(0.9f, 1.5f);
		_speed = math::random(0.8f, 1.2f);
		_y = math::random(300.f, 600.f);
		_x = Render::device.Width() + _scale * _cloud->getBitmapRect().Width();
	}
}