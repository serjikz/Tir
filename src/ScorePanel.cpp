#include "stdafx.h"
#include "ScorePanel.h"

ScorePanel::ScorePanel(rapidxml::xml_node<>* settings)
	:Panel(settings)
{
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	rapidxml::xml_node<>* backSideRectSettings = settings->first_node("backSideRect");
	float x = Xml::GetFloatAttributeOrDef(backSideRectSettings, "x", 0.f);
	float y = Xml::GetFloatAttributeOrDef(backSideRectSettings, "y", 0.f);
	float scale = Xml::GetFloatAttributeOrDef(backSideRectSettings, "scale", 1.f);
	_alphaMiultiplier = Xml::GetFloatAttributeOrDef(backSideRectSettings, "alpha", 1.f);
	_backSideRect = IRect(x, y, scale * _textureCenter.x, scale * _textureCenter.y);
}

void ScorePanel::draw() {
	if (_state != State::HIDEN) {
		Render::BeginAlphaMul(_t);
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_x, _y, 0);
		Render::device.MatrixScale(_splineVal, _splineVal, 1.f);
		Render::device.MatrixTranslate(-_textureCenter.x, -_textureCenter.y, 0);	
		Render::BeginAlphaMul(_alphaMiultiplier *_t);
		Render::device.SetTexturing(false);
		Render::BeginColor(Color::BLACK);
		Render::DrawRect(_backSideRect);
		Render::EndColor();
		Render::EndAlphaMul();
		Render::device.SetTexturing(true);
		_tex->Draw();
		Render::device.PopMatrix();
		Render::EndAlphaMul();
	}
}
