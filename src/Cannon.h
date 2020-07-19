#pragma once

class Cannon
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	float _angle;
public:
	Cannon(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cannon> HardPtr;
	void draw();
	void update(float dt);
};