#include "stdafx.h"
#include "ScorePanel.h"

ScorePanel::ScorePanel(rapidxml::xml_node<>* settings)
	:Panel(settings),
	_text(""),
	_textX(0),
	_textY(0)
{
	_textureCenter = FPoint(_tex->getBitmapRect().Width() / 2.f, _tex->getBitmapRect().Height() / 2.f);
	rapidxml::xml_node<>* backSideRectSettings = settings->first_node("backSideRect");
	float x = Xml::GetFloatAttributeOrDef(backSideRectSettings, "x", 0.f);
	float y = Xml::GetFloatAttributeOrDef(backSideRectSettings, "y", 0.f);
	float scale = Xml::GetFloatAttributeOrDef(backSideRectSettings, "scale", 1.f);
	_alphaMiultiplier = Xml::GetFloatAttributeOrDef(backSideRectSettings, "alpha", 1.f);
	_backSideRect = IRect(x, y, scale * _textureCenter.x, scale * _textureCenter.y);
	_textX = Xml::GetIntAttributeOrDef(settings, "textX", 0);
	_textY = Xml::GetIntAttributeOrDef(settings, "textY", 0);
	_restartButton = Button::HardPtr(new Button(settings->first_node("button")));
}


void ScorePanel::update(float dt) {
	Panel::update(dt);
	_restartButton->update(dt);
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
		Render::BindFont("FloralessTime");
		Render::PrintString(_textX, _textY, _text, 1.f, CenterAlign, CenterAlign);
		Render::device.SetTexturing(true);
		_tex->Draw();
		_restartButton->draw();
		Render::device.PopMatrix();
		Render::EndAlphaMul();
	}
}

void ScorePanel::setStatisticsMsg(const std::string& msg) {
	_text = msg;
}

void ScorePanel::mouseMove(const IPoint& mouse_pos) {
	IPoint shift = IPoint(_x - _textureCenter.x, _y - _textureCenter.y);
	_restartButton->mouseMove(mouse_pos - shift);
}