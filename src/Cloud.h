#pragma once


class Cloud : public BkgObject
{
private:	
	
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
	virtual void draw();
	virtual void update(float dt);
};