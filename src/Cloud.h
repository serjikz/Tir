#pragma once

class Cloud
{
private:	
	Render::Texture* _cloud;
	short int _x, _y;
	float _scale;
	float _speed;
	float _alpha;
public:
	Cloud (rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Cloud> HardPrt;
	void draw();
	void update(float dt);
};