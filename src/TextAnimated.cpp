#include "stdafx.h"
#include "TextAnimated.h"

TextAnimated::TextAnimated(std::string text, int x, int y)
	:_x(x),
	_y(y),
	_text(text)
{
}

void TextAnimated::draw() {
	/*assert(_wheel);
	FPoint textureCenter = FPoint(_wheel->getBitmapRect().Width() / 2, _wheel->getBitmapRect().Height() / 2 );
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	Render::device.MatrixTranslate(-textureCenter.x, -textureCenter.y, 0);
	_wheel->Draw();
	Render::device.PopMatrix();*/
}

void TextAnimated::update(float dt) {
	
}