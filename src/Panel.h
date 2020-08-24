#pragma once

class Panel
{
protected:	
	const float EPS = 0.01f;
	Render::Texture* _tex;
	short int _x, _y;
	float _splineVal;
	float _t;
	float _speed;
	float _direction;
	TimedSpline<float> _spline;
public:
	enum class State {
		HIDEN,
		NORMAL,
		APEARENCE,
		DISSAPEARENCE
	} _state;
	Panel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Panel> HardPtr;
	virtual void draw();
	virtual void update(float dt);
	virtual void setState(Panel::State newState);
};