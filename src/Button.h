#pragma once

class Button
{
protected:	
	Render::Texture* _tex;
	short int _x, _y;
	float _splineVal;
	float _t;
	float _speed;
	TimedSpline<float> _spline;
public:
	Button(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Button> HardPtr;
	void draw();
	void update(float dt);
	void mouseDown(const IPoint& mouse_pos);
	void mouseMove(const IPoint& mouse_pos);
};