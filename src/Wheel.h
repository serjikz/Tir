#pragma once

class Wheel
{
private:	
	Render::Texture* _wheel;
	FPoint _textureCenter;
	short int _x, _y;
	float _angle;
public:
	Wheel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Wheel> HardPtr;
	void draw();
	void update(float dt);
};