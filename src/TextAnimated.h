#pragma once
#include "InterfaceObject.h"

class TextAnimated : public InterfaceObject
{
private:
	const float SPEED = 4.f;
	const float DELTA_SCALE = 0.03f;
	const float EPS = 0.01f;
	float _scale;
	float _t;
	float _alpha;
	std::string _text;	
public:
	TextAnimated(const std::string& text, int x, int y);
	typedef boost::shared_ptr<TextAnimated> HardPtr;
	void draw();
	void update(float dt);
	virtual void setState(InterfaceState newState);
};