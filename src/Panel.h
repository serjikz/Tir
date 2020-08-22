#pragma once

class Panel
{
private:	
	Render::Texture* _tex;
	short int _x, _y;
	float _angle;
public:
	Panel(rapidxml::xml_node<>* settings);
	typedef boost::shared_ptr<Panel> HardPtr;
	void draw();
	void update(float dt);
};