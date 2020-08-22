#include "stdafx.h"
#include "TextAnimated.h"

TextAnimated::TextAnimated(const std::string& text, int x, int y)
	:_x(x),
	_y(y),
	_text(text)
{
}

void TextAnimated::draw() {
	Render::BindFont("FloralessTap");
	Render::PrintString(_x, _y, _text, 1.f, CenterAlign, BottomAlign);
}

void TextAnimated::update(float dt) {
	
}