#include "stdafx.h"
#include "ScorePanel.h"

ScorePanel::ScorePanel(rapidxml::xml_node<>* settings)
	:Panel(settings)
{
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
}

void ScorePanel::draw() {
	if (_state != State::HIDEN) {
		Render::BeginAlphaMul(_t);
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _y, 0);
		Render::device.MatrixScale(_splineVal, _splineVal, 1.f);
		Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);
		_tex->Draw();
		Render::device.PopMatrix();
		Render::EndAlphaMul();
	}
}
