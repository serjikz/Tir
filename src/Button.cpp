#include "stdafx.h"
#include "Button.h"

Button::Button(rapidxml::xml_node<>* settings)
	: _x(0),
	  _y(0),
	_t(0.f)
{
	std::string textureID = Xml::GetStringAttributeOrDef(settings, "textureID", "");
	_tex = Core::resourceManager.Get<Render::Texture>(textureID);
	_x = Xml::GetIntAttributeOrDef(settings, "x", 0);
	_y = Xml::GetIntAttributeOrDef(settings, "y", 0);
	_speed = Xml::GetIntAttributeOrDef(settings, "speed", 1.f);
	rapidxml::xml_node<>* splinePoints = settings->first_node("spline");
	while (splinePoints) {
		float t = Xml::GetFloatAttributeOrDef(splinePoints, "t", 0.f);
		float value = Xml::GetFloatAttributeOrDef(splinePoints, "value", 0.f);
		_spline.addKey(t, value);
		splinePoints = splinePoints->next_sibling();
	}
	_spline.CalculateGradient();
}

void Button::draw() {
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_x, _splineVal, 0);
	_tex->Draw();
	Render::device.PopMatrix();
}

void Button::update(float dt) {
	_t = math::clamp(0.f, 1.f, _t + _speed *  dt);
	_splineVal = _spline.getGlobalFrame(_t);
}

void Button::mouseDown(const IPoint& mouse_pos) {

}

void mouseMove(const IPoint& mouse_pos) {
	
}