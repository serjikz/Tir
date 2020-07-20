#pragma once

class Cannon
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	short int _dx, _dy;
	float _angle;
	float _scaleY;
	float _t;
	float MIN_ANGLE;
	float MAX_ANGLE;
public:
	Cannon(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cannon> HardPtr;
	void draw();
	void update(float dt, float tankPosx);
	void shot();
};