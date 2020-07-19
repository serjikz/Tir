#pragma once

class Cloud
{
private:	
	Render::Texture* _cloud;
	short int _x, _y;
	float _scale;
	float _speed;
	float ALPHA;
	float MIN_SCALE;
	float MAX_SCALE;
	float MIN_SPEED;
	float MAX_SPEED;
	float MIN_Y;
	float MAX_Y;
public:
	Cloud (rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cloud> HardPtr;
	void draw();
	void update(float dt);
};