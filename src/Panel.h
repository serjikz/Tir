#pragma once

class Panel
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	float _t;
	float _speed;
	TimedSpline<float> _spline;
public:
	enum class State {
		HIDEN,
		NORMAL,
		APEARENCE
	} _state;
	Panel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Panel> HardPtr;
	void draw();
	void update(float dt);
	void setState(Panel::State newState);
};