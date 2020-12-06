#pragma once
#include "InterfaceObject.h"

class TextAnimated : public InterfaceObject
{
private:
	const float EPS = 0.01f;
	const std::string FONT_NAME = "FloralessTap";
	float _deltaScale;
	float _scale;
	float _speed;
	float _t;
	float _alpha;
	std::string _text;	
public:
	TextAnimated(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<TextAnimated> HardPtr;
	void draw();
	void update(float dt);
	virtual void setState(InterfaceState newState);
};