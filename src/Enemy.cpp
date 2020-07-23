#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(rapidxml::xml_node<>* settings)
	: _x(0),
	_speed(0),
	_angle(0)
{	
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_texture = Core::resourceManager.Get<Render::Texture>(textureID);	
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
	_texture->Draw();
	Render::device.PopMatrix();	
}
