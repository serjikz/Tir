#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(rapidxml::xml_node<>* settings)
	: _x(100),
	_y(100)
{	
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_texture = Core::resourceManager.Get<Render::Texture>(textureID);	
	_textureCenter = FPoint(_texture->getBitmapRect().Width() / 2.f, _texture->getBitmapRect().Height() / 2.f);
	_vecMove.x = 160;
	_vecMove.y = 160;
};

void Enemy::update(float dt) {
	_x += _vecMove.x * dt;
	_y += _vecMove.y * dt;
	checkGameFieldCollision();
}

void Enemy::draw() {
	
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	//Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	//Render::device.MatrixScale(1.f, _scaleY, 1.f);
	Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
	_texture->Draw();
	Render::device.PopMatrix();	
}

void Enemy::checkGameFieldCollision() {
	if (_x + _textureCenter.x > Render::device.Width() || _x - _textureCenter.y < 0) {
		_vecMove.x *= -1;
	}
	if (_y + _textureCenter.y > Render::device.Height() || _y - _textureCenter.y < 0) {
		_vecMove.y *= -1;
	}
}