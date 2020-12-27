#pragma once
#include "InterfaceObject.h"

// Базовый класс панели
class Panel : public InterfaceObject
{
protected:	
	const float EPS = 0.01f;
	Render::Texture* _tex;
	FPoint _textureCenter;
	float _splineVal;
	float _t;
	float _speed;
	
	TimedSpline<float> _spline;
public:
	Panel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Panel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(InterfaceState newState) {};
	virtual void setState(InterfaceObject::State newState);
};