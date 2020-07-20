#pragma once

class Cannon
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	float _angle;
	float MIN_ANGLE;
	float MAX_ANGLE;
public:
	Cannon(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cannon> HardPtr;
	void draw();
	void update(float tankPosx);
};